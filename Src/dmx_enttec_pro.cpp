/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2013  Christoph Guillermet
       WWWWWWWWWWWWWWW           |
     WWWWWWWWWWWWWWWWWWW         | This file is part of White Cat.
    WWWWWWWWWWWWWWWWWCWWWW       |
   WWWWWWWWWWWWWWWWW tWWWWW      | White Cat is free software: you can redistribute it and/or modify
  WWWW   WWWWWWWWWW  tWWWWWW     | it under the terms of the GNU General Public License as published by
 WWWWWt              tWWWWWWa    | the Free Software Foundation, either version 2 of the License, or
 WWWWWW               WWWWWWW    | (at your option) any later version.
WWWWWWWW              WWWWWWW    |
WWWWWWWW               WWWWWWW   | White Cat is distributed in the hope that it will be useful,
WWWWWWW               WWWWWWWW   | but WITHOUT ANY WARRANTY; without even the implied warranty of
WWWWWWW      CWWW    W WWWWWWW   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
WWWWWWW            aW  WWWWWWW   | GNU General Public License for more details.
WWWWWWWW           C  WWWWWWWW   |
 WWWWWWWW            CWWWWWWW    | You should have received a copy of the GNU General Public License
 WWWWWWWWW          WWWWWWWWW    | along with White Cat.  If not, see <http://www.gnu.org/licenses/>.
  WWWWWWWWWWC    CWWWWWWWWWW     |
   WWWWWWWWWWWWWWWWWWWWWWWW      |
    WWWWWWWWWWWWWWWWWWWWWW       |
      WWWWWWWWWWWWWWWWWWa        |
        WWWWWWWWWWWWWWW          |
           WWWWWWWWt             |
                                 |
---------------------------------------------------------------------------------------------------------------*/

/**

* \file dmx_enttec_pro.cpp
* \brief {send dmx fonctions to the enttec usb pro}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gère les envoie du data dmx et autre fonction vers l'enttec usb pro, specifique pour windows
*
*   send dmx data and other fonctions to the enttec usb pro, only for windows
*
 **/
//enttec pro
//pour code enttec pro:
#include <process.h>
#include <assert.h>
#include <tchar.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////ENTTEC PRO is seperated from other dmx interfaces/////////////
//////////////////because you do not load a dll you search for regitry entry////
//////////////////and write to this entry directly//////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uint8_t Num_Devices =0; // nbre de devices detected


#define GET_WIDGET_PARAMS 3
#define GET_WIDGET_PARAMS_REPLY 3
#define SET_WIDGET_PARAMS 4
#define SET_DMX_RX_MODE 5
#define SET_DMX_TX_MODE 6
#define SEND_DMX_RDM_TX 7
#define RECEIVE_DMX_ON_CHANGE 8
#define RECEIVED_DMX_COS_TYPE 9

#pragma pack(1)
typedef struct {
        unsigned char FirmwareLSB;
        unsigned char FirmwareMSB;
        unsigned char BreakTime;
        unsigned char MaBTime;
        unsigned char RefreshRate;
}DMXUSBPROParamsType;

typedef struct {
        unsigned char UserSizeLSB;
        unsigned char UserSizeMSB;
        unsigned char BreakTime;
        unsigned char MaBTime;
        unsigned char RefreshRate;
}DMXUSBPROSetParamsType;
#pragma pack()

struct ReceivedDmxCosStruct
{
	unsigned char start_changed_byte_number;
	unsigned char changed_byte_array[5];
	unsigned char changed_byte_data[40];
};

BOOL res = false;
BOOL resIn = false;
unsigned char DeviceName[256];
unsigned char DeviceNameIN[256];
// old school globals
HANDLE com_handle_ = NULL;
HANDLE com_handle_IN = NULL;
unsigned char DMXData_frame1_[512];

DMXUSBPROParamsType params_;


int Enttec_Pro_SetCommParams()
{
	// SetCommState & Timeouts
	DCB dcb;
	GetCommState(com_handle_, &dcb);

//	dcb.fBinary = TRUE; /* binary mode, no EOF check */
//	dcb.fErrorChar = FALSE; /* disable error replacement */
//	dcb.fAbortOnError = FALSE;

	dcb.fBinary = true; /* binary mode, no EOF check */
	dcb.fErrorChar = false; /* disable error replacement */
	dcb.fAbortOnError = false;
	/* Set the baud rate */
	dcb.BaudRate = 57600;

	/* Set the data characteristics */
	dcb.ByteSize = 8; /* 8 data bits */
	dcb.StopBits = ONESTOPBIT; /* 1 stop bit */
	dcb.fParity = NOPARITY; /* no parity */
	dcb.Parity = 0;

	/* diable all flow control stuff */
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fInX = FALSE;
	dcb.fOutX = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fOutxCtsFlow = FALSE;

	SetCommState(com_handle_, &dcb);

    COMMTIMEOUTS timeouts;
	GetCommTimeouts(com_handle_, &timeouts);
	/* set timimg values */
	timeouts.ReadIntervalTimeout = 500;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.ReadTotalTimeoutConstant = 500;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 500;

	SetCommTimeouts(com_handle_, &timeouts);

	return (0);
}


#define SEND_ON_CHANGE_MODE

#define READ_ONE_BYTE(handle,byte,bytes_read,overlapped_struct) ReadFile(handle,byte,1,bytes_read,overlapped_struct)


// send a packet, overlapped code has not been implemented yet
int Enttec_Pro_SendData(int label, unsigned char *data, unsigned int length, LPOVERLAPPED lpOverlapped)
{

//label is SEND_DMX_RDM_TX
	BOOL res = false;
	DWORD bytes_written = 0;
	//HANDLE event = NULL;

	unsigned char header[4];
	header[0] = 0x7E;
	header[1] = label;
	header[2] = length & 0xFF;
	header[3] = length >> 8;

	res = WriteFile(
		com_handle_,					//Instance de votre accès au port série
		(unsigned char *)header,		//Pointeur sur la donnée à écrire
		4,								//Nombre de bytes à écrire
		&bytes_written,					//pointeur to number of bytes written
		lpOverlapped					//Doit être NULL pour windows CE
	);
	if (!res || (bytes_written != 4)) return -1;


	res = WriteFile(
		com_handle_,					//Instance de votre accès au port série
		(unsigned char *)data,			//Pointeur sur la donnée à écrire
		length,							//Nombre de bytes à écrire
		&bytes_written,					//pointeur to number of bytes written
		lpOverlapped			        //Doit être NULL pour windows CE
	);
	if (!res || (bytes_written != length)) return -1;


	unsigned char end_code = 0xE7;
	res = WriteFile(
		com_handle_,					//Instance de votre accès au port série
		(unsigned char *)&end_code,		//Pointeur sur la donnée à écrire
		1,								//Nombre de bytes à écrire
		&bytes_written,					//pointeur to number of bytes written
		lpOverlapped					//Doit être NULL pour windows CE
	);
	if (!res || (bytes_written != 1)) return -1;

	return 0;
}




int Enttec_Pro_SetCommParamsIN()
{
	// SetCommState & Timeouts
	DCB dcbIN;
	GetCommState(com_handle_IN, &dcbIN);

//	dcbIN.fBinary = TRUE; /* binary mode, no EOF check */
//	dcbIN.fErrorChar = FALSE; /* disable error replacement */
//	dcbIN.fAbortOnError = FALSE;


	dcbIN.fBinary = true; /* binary mode, no EOF check */
	dcbIN.fErrorChar = false; /* disable error replacement */
	dcbIN.fAbortOnError = false;

	/* Set the baud rate */
	dcbIN.BaudRate = 57600;

	/* Set the data characteristics */
	dcbIN.ByteSize = 8; /* 8 data bits */
	dcbIN.StopBits = ONESTOPBIT; /* 1 stop bit */
	dcbIN.fParity = NOPARITY; /* no parity */
	dcbIN.Parity = 0;

	/* diable all flow control stuff */
	dcbIN.fDtrControl = DTR_CONTROL_DISABLE;
	dcbIN.fRtsControl = RTS_CONTROL_DISABLE;
	dcbIN.fInX = FALSE;
	dcbIN.fOutX = FALSE;
	dcbIN.fOutxDsrFlow = FALSE;
	dcbIN.fOutxCtsFlow = FALSE;

	SetCommState(com_handle_IN, &dcbIN);

    COMMTIMEOUTS timeoutsIN;
	GetCommTimeouts(com_handle_IN, &timeoutsIN);
	/* set timimg values */
	timeoutsIN.ReadIntervalTimeout = 500;
	timeoutsIN.ReadTotalTimeoutMultiplier = 10;
	timeoutsIN.ReadTotalTimeoutConstant = 500;
	timeoutsIN.WriteTotalTimeoutMultiplier = 10;
	timeoutsIN.WriteTotalTimeoutConstant = 500;

	SetCommTimeouts(com_handle_IN, &timeoutsIN);

	return 0;
}

/* Function : ReceiveData
 * Author	: ENTTEC
 * Purpose  : Receives the passed Frame from the PRO
 * Parameters: label , Frame Data Packet , Expected Length (Size of Frame)
 **/

uint16_t Enttec_Pro_ReceiveData(uint16_t label, uint8_t *data, uint32_t expected_length)
{

	BOOL resIn = 0;
	DWORD length = 0;
	DWORD bytes_read = 0;
	uint8_t byte = 0;
	//HANDLE eventIN = NULL;
	char buffer[513];

	while (byte != label)
	{
		while (byte != 0x7E )
		{
			resIn = READ_ONE_BYTE(com_handle_IN,(uint8_t *)&byte,&bytes_read,NULL );
			if (!resIn || (bytes_read != 1)) return  0;
		}
		if (byte != 0x7E ) continue;

		resIn = READ_ONE_BYTE(com_handle_IN,(uint8_t *)&byte,&bytes_read,NULL );
		if (!resIn || (bytes_read != 1)) return  0;
	}

	resIn = READ_ONE_BYTE(com_handle_IN,(uint8_t *)&byte,&bytes_read,NULL );
	if (!resIn || (bytes_read != 1)) return  0;
	length = byte;


	resIn = READ_ONE_BYTE(com_handle_IN,(uint8_t *)&byte,&bytes_read,NULL );
	if (!resIn || (bytes_read != 1)) return  0;
	length += ((uint32_t)byte)<<8;

	if (length > 513)
		return  0;

	resIn = ReadFile(com_handle_IN,buffer,length,&bytes_read,NULL );
	if (!resIn || (bytes_read != length)) return  0;

	resIn = READ_ONE_BYTE(com_handle_IN,(uint8_t *)&byte,&bytes_read,NULL );
	if (!resIn || (bytes_read != 1)) return  0;
	if (byte != 0xE7) return  0;

	memcpy(data,buffer,expected_length);

	return expected_length;
}


int Detect_EnttecProOut()
{
com_handle_ = NULL;
	// Search in Windows Registry for serial COM
	{
		HKEY        hKey;
        DWORD       DeviceNameLen, KeyNameLen;
        char		KeyName[256];
		intptr_t idmx ;//modification 2 aout était int idmx; pb de pointeur 32 vers 64
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
        {
			 sprintf(string_display_dmx_params,"No VCOM drivers installed !");
             return(0);
        }
        idmx = 0;
        while(idmx < 50) {
            DeviceNameLen = 80;
            KeyNameLen = 100;
            if (RegEnumValue(hKey,idmx,KeyName,&KeyNameLen,NULL,NULL,DeviceName,&DeviceNameLen) != ERROR_SUCCESS) break;

			if ((!strncmp(KeyName,"\\Device\\VCP",11)) && idmx!=arduino_com0)
			{
                index_init_dmx_ok[3]=1;
                istheresomeone_in_enttecpro=idmx;
                break;
				// we found a serial COM device, COM port "idmx"
			}

			DeviceName[0] = 0;

            idmx++;
		}



		RegCloseKey(hKey);

		if (idmx == 50)
		{
			 sprintf(string_display_dmx_params,"No ENTTEC PRO detected. ");
             return(0);
		}
	sprintf(string_display_dmx_params,"ENTTEC PRO Out is on : %s",DeviceName);
	}

return(0);
}

int Open_EnttecProOut()
{
 	char com_str[10];
	sprintf(com_str,"%s:",DeviceName);
	LPSTR lpszPortName = _T(com_str);
	com_handle_ = CreateFile(
		lpszPortName,
		GENERIC_READ | GENERIC_WRITE,
		0,								// DWORD dwShareMode,
		NULL,							// LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		OPEN_EXISTING,					// DWORD dwCreationDispostion,
		0, //FILE_FLAG_OVERLAPPED,		// DWORD dwFlagsAndAttributes,
		NULL							// HANDLE hTemplateFile
	);

	int iRet = (int)(com_handle_ );

	if (iRet<0)
	{
    com_handle_ = NULL;
    index_init_dmx_ok[3]=0;
	sprintf(string_display_dmx_params,"Impossible to open ENTTEC PRO Out, is it PLUGGED ?");
    return(0);
	}

	// SetCommState & Timeout
    Enttec_Pro_SetCommParams();

	// flush rx & tx buffers
	res = FlushFileBuffers(com_handle_);
	if (!res)
	{
    sprintf(string_display_dmx_params,"ENTTEC PRO Out: Flush file buffers failed...");
	CloseHandle(com_handle_); com_handle_ = NULL;
	return(0);
	}
return(0);
}

int Close_EnttecProOut()
{
CloseHandle(com_handle_); com_handle_ = NULL;
sprintf(string_display_dmx_params,"ENTTEC PRO OUT : Closed...");
return(0);
}


int Detect_EnttecProIn()
{
com_handle_IN = NULL;
	// Search in Windows Registry for serial COM
	{
		HKEY        hKeyIN;
        DWORD       DeviceNameLenIN, KeyNameLenIN;
        char		KeyNameIN[256];
		intptr_t idmxIN ;//modification 2 aout était int idmx; pb de pointeur 32 vers 64
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_QUERY_VALUE, &hKeyIN) != ERROR_SUCCESS)
        {
			 sprintf(string_display_dmx_params,"Impossible to load DLL");return(0);
        }
        idmxIN = istheresomeone_in_enttecpro+1;//depart après position enttec pro out
        while(idmxIN < 50) {
            DeviceNameLenIN = 80;
            KeyNameLenIN = 100;
            if (RegEnumValue(hKeyIN,idmxIN,KeyNameIN,&KeyNameLenIN,NULL,NULL,DeviceNameIN,&DeviceNameLenIN) != ERROR_SUCCESS) break;

			if (!strncmp(KeyNameIN,"\\Device\\VCP",11))
			{
                sprintf(string_display_dmx_params,"detected Vcom in %d!",idmxIN);
                index_init_EnttecPROIN_ok=1;
                vcom_inposition_is=idmxIN;
				// we found a serial COM device, COM port "idmx"
				break;
			}

			DeviceNameIN[0] = 0;
            idmxIN++;
		}
		RegCloseKey(hKeyIN);

		if (idmxIN == 50)
		{
			sprintf(string_display_dmx_params,"No VCOM for IN founded. ");
             return(0);
		}
	sprintf(string_display_dmx_params,"Founded Enttec Pro In :%s",DeviceNameIN);
	}
 return(0);
}

int Open_ProIn()
{
 	char com_str[10];
	sprintf(com_str,"%s:",DeviceNameIN);
	LPSTR lpszPortName = _T(com_str);
	com_handle_IN = CreateFile(
		lpszPortName,
		GENERIC_READ | GENERIC_WRITE,
		0,								// DWORD dwShareMode,
		NULL,							// LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		OPEN_EXISTING,					// DWORD dwCreationDispostion,
		0, //FILE_FLAG_OVERLAPPED,		// DWORD dwFlagsAndAttributes,
		NULL							// HANDLE hTemplateFile
	);

	int iRetIn = (int)(com_handle_IN );

	if (iRetIn<0)
	{
    com_handle_IN = NULL;
	sprintf(string_display_dmx_params,"Impossible to open interface, is it PLUGGED ?");
    return(0);
	}
	 else {sprintf(string_display_dmx_params,"Enttec Pro IN  %s is now Open",DeviceNameIN);}

	// SetCommState & Timeout
    Enttec_Pro_SetCommParamsIN();

	// flush rx & tx buffers
	resIn = FlushFileBuffers(com_handle_IN);
	if (!resIn)
	{
    sprintf(string_display_dmx_params,"\ENTTEC PRO IN %s: Flush file buffers failed...",DeviceNameIN);
	CloseHandle(com_handle_IN); com_handle_IN = NULL;
	return(0);
	}
	index_init_EnttecPROIN_ok=1;
    return(0);
}

int Close_ProIn()
{
 CloseHandle(com_handle_IN); com_handle_IN = NULL;
 sprintf(string_display_dmx_params,"Enttec Pro IN %s is now closed",DeviceNameIN) ;
 index_init_EnttecPROIN_ok=0;
 return(0);
}

