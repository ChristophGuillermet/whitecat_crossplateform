whitecat_crossplateform short Features description
===================================================
WhiteCat Lighting Board is a free lighting desk for windows developped by Christoph Guillermet.

It can do a lot of stuff of course as lighting desk,artnet and dmx interfaces, cue, chanel macro, patch, xy mover and trichromie(not totally usefull actuely for motor lighting), etc...

But he has a lot of strange or useful other fonctions who make it able to be used for something else than linghting.

It can play sound, controle Arduino and Arduino HF prototype for electronique developpement, has a little video tracking module, an echo (sort of gravity and physical fonction of control), a draw module (to draw directly the light), a plot module to draw your light plot directly in whitecat and in sync with the soft, and a remote for iphone and ipad thrue iFantastick soft.
 
To start using the cat
====================
- At http://www.le-chat-noir-numerique.fr/whitecat/dokuwiki/doku.php you can find :
    - a complete doc on the wiki page,
    - and a shorter one in english

- on whitecat's website, http://www.le-chat-noir-numerique.fr, the forum is very useful, and there are some vidéo tutorials

- you can download the last beta release at http://www.le-chat-noir-numerique.fr/release or from the main page, just uncompress the zip at C:/ and enjoy.

Licence
=======
White Cat is free software developped originaly by Cristoph Guillermet: you can redistribute it and/or modify

it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or(at your option) any later version.

White Cat is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with White Cat.  If not, see<http://www.gnu.org/licenses/>.

To start coding quickly:
==============
In windows :
-Follow the PREBUILD_INSTALL_WITH_CODEBLOCKS_AND_MINGW4.8.1.txt or the PREBUILD_INSTALL_With_DEV_C++_AND_MINGW4.8.1.txt

- if you want build yourself the libraries for an other plateform or compilator than MinGW4.8.1, you can get inspiration from the BUILD_LIBRARIES_INSTRUCTIONS_for_MinGW.txt

The API documentation
=====================
You can find a short doc genereted by doxygen in the API.
If you code an contribute to the whitecat project, please continue to comment your code with the doxigen format, for the others. 
If you are french a tutorial for doxygen and whitecat can be found at http://www.le-chat-noir-numerique.fr/whitecat/dokuwiki/doku.php?id=documentation_doxygen

Content of the repository
============
Sources to to build whitecat as crossplateform with:
For crossplateform:
Allegro 4.4.2 modified, opencv 2.4.8, Openlayer 2.1 modified, Audiere1.9.4, MidiShare1.9.1, libharu2.0.8

For windows:
-CSerial (for the arduino communication)
-dashard (sunlight dmx interface)
-opendmx
-enttec usb pro

For OSX, Debian, unix and linux POSIX systeme (must be developed):
- Audiere 1.9.5
- libserial 0.5.2 (to replace Cserial in system non windows)

The libs sources can be cloned from the whitecatlib repository at https://github.com/ChristophGuillermet/whitecatlib
The builds of whitecat from the whitecatbuild repository at https://github.com/ChristophGuillermet/whitecatbuild

If you are french, for how to use git a tuto is at http://www.le-chat-noir-numerique.fr/whitecat/dokuwiki/doku.php?id=recettes_pour_git

This two folder must cloned or copy inside the whitecat_crossplateform folders but you may find some lighter Prebuilds for this two repository for your environement and DEVKIT at : http://www.le-chat-noir-numerique.fr/coding/

