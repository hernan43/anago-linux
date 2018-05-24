Famicom ROM Cartridge Utility - Anago
by Unagi development team and contributors
official project page http://unagi.sourceforge.jp/
BBS http://unagi.sourceforge.jp/t/bbs.html

--Infoduction--
Anago is a fork of the origional Unagi utility, supporting only the Kazzo USB
Famicom bus simulator and compatible hardware. Anago dumps at about the same
speed as Unagi but writes flash carts with PRG and CHR ROM faster thanks to
programming both in parallel.

--command line arguments--
anago mode script_file target_file [...]

==Dump Mode==
Used to create iNES ROM images from carts.
anago dPC script_file dump_file mapper
d?? or D??
  If given, the ?? portion determines the length of the ROM to dump in multiples
  of the mapper's configured width for the program ROM portion and character ROM
  portion respectively. For example, UNROM boards use 128KB PRG ROMs while UOROM
  boards use 256KB ROMs. A dumper script is provided for UNROM. To dump a UOROM
  board, use the UNROM script with the d2 option.
  2 is applicable for unrom.ad, mmc3.ad and mmc5.ad
  4 is applicable for mmc5.ad
D?? - Dumpping progress display is same as unagi.exe.
script_file - Specifies .ad file for target cartridge.
dump_file - Output file, typically ending in .nes,
mapper - Overrides the mapper number in the output iNES ROM image. This is
  useful for mapper ASICs that are assigned multiple iNES mapper numbers such as
  MMC3/6.

example1.1: Getting an image for UNROM
> anago.exe d unrom.ad unrom.nes
anago get vram mirroring connection from target cartridge.

example1.2: Getting an image for UOROM
> anago.exe d2 unrom.ad unrom.nes
UOROM data size is twice that of UNROM. This must be specicifed by hand.

example2: Getting an image for Metal Slader Glory / ELROM
> anago.exe d22 mmc5.ad hal_4j.nes
In many cases, it is enough by 2M+2M to dump images for MMC5. MMC5 can 
manage 8M+8M. Please specify it individually according to capacity. 

example3: Getting an image for Ys III / TKSROM
> anago.exe d mmc3.ad vfr_q8_12.nes 118
Enter digits on last commandline word to change mapper number for MMC3 
variants. 

==Flash Programming Mode==
Write to Flash ROM chips on specially prepaired flash carts.

anago.exe f?? script_file programming_file prg_chip chr_chip
f?? or F?? - 
  If given, the "??" portion controls the fill mode for the PRG and CHR Flash
  ROM chips respectively. If omitted, Fill Mode is assumed.
  'f' Fill mode. The entire ROM chip is overwritten, duplicating the PRG or CHR
      ROM contents as many times as nessecary to fill the chip. This is the
      slowest option but may be needed under some curcumstances. If unsure, use
      this mode. In general, if your mapper has an unknonw power-on state or the
      top address lines of the ROM may float at runtime, always use this mode.
  't' Only writes the ROM image once to the top-most portion of the chip. This
      mode is typically safe for CHR-ROM for any mapper, as the power-on state
      is immaterial with a proper initialization routine.
  'b' Only writes the ROM image once to the bottom-most portion of the chip. Use
      with caution, most mapper's power-on states are incompatible with this
      mode.
  'e' Write nothing for this memory device. This is equivalent to specifiying a
      dummy device.
F?? - Validate written memory and abort if there is a discrepancey.
script_file - Specifies .af file for target cartridge.
programming)file - Specifies the input iNES image file.
prg_chip, chr_chip -
  Specifies the Flash ROM chip present for each memory type in the target flash
  cart. Supported devices are listed in "flashdevice.nut". "dummy" is a special
  device name that will transfer no data. Use this to avoid overwriting one of
  the memory chips.

example1.1: Tranfer 1M+1M image to mmc3 / TLROM.
> anago.exe f mmc3.af tlrom_1M_1M.nes AM29F040B AM29F040B
In this case the board is configured with 4M flash ROMs. The MMC3 can only map
2M of CHR-ROM, so the high address line is assumed to be tied (either high or
low). Anago would transfer the PRG portion four times to fill the PRG chip, and
the CHR portion two times to fill the CHR chip.

example1.2: Tranfer 1M+1M image to mmc3 / TLROM.
> anago.exe ftt mmc3.af tlrom_1M_1M.nes AM29F040B AM29F040B
In this example the PRG and CHR ROMs are only written once, this time to the top
portion of each chip, in order to save time. The program code will need to be
aware of this arrangement and only use the top-most bank numbers.

example1.3: Tranfer 1M+1M image to mmc3 / TLROM.
> anago.exe fbt mmc3.af tlrom_1M_1M.nes AM29F040B AM29F040B
In this example the PRG ROM is written to the bottom 1M of the PRG ROM chip and
the CHR ROM is written to the top 1M of the CHR ROM chip. The origional author
remarks that this often works with Konami and Namcot titles. 

Incidentally, mmc3 is not compatible with Namcot 109. The 109 board has hard-
wired vram mirroring, mmc3 does not. Furthermore Namcot 106 is a fictitious
device with well known extra sound. Don't miss 109 and 106.
* Note that the second translator does not fully understand the meaning of the
* above paragraph.

example2: tranfer UNROM(1M) image to UOROM.
> anago.exe ft uorom.af unrom.nes AM29F040B
If charcter memory is RAM, charcter device can be skip. Again the program will
need to only use the upper bank numbers.

example3: Transfferring only charcter ROM image to mmc1/ SLROM
> anago.exe ftt mmc1_slrom.af skrom.nes dummy AM29F040B
> anago.exe fet mmc1_slrom.af skrom.nes AM29F040B AM29F040B
Both commands result in the same behavior. Choose the one that suits your taste.

--Notes--
- If the concepts of Top and Bottom transfer are not clear, and their impact and
  requirements on your software are not obvious, please use the full transfer
  mode at all times.
- Anago does not have WRAM reading or writing mode at this time. Plase use the
  Unagi utility for this purpose if needed.

** Below section from origional document and is incomplete. More complete
   dependancies available in COMPILING.txt
--used libaries---
[LibUSB-Win32]
Copyright (c) 2002-2004 Stephan Meyer, <ste_meyer@web.de>
Copyright (c) 2000-2004 Johannes Erdfelt, <johannes@erdfelt.com>
Copyright (c) Thomas Sailer, <sailer@ife.ee.ethz.ch>
[SQUIRREL 2.1.2 stable] Copyright (c) 2003-2007 Alberto Demichelis
[opendevice.c] (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH

