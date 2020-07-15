# WorkFromHome
//Following is the program is developped by A. R. Ansari 
//It will read intel hex file having no extended linear address that is it has maxlimit of 0xFFFF addressing 64K Bytes..16 bit.
//example of use  in windows where first argument is filnename, 2nd argument is hex address ,3rd argument is in hex index of page and the last argument is in decimal the number of bytes to be read from the provided index of page...
//it shoudld be note that  2nd arg+ 3rd arg=>256 bytes otherwig++ DataRetriveFromIntelBuffer16.cpp -o DataRetriveFromIntelBuffer1se it will rounded up under 256.
//Compile source file and keep hex file in the same folder
//g++ DataRetriveFromIntelBuffer16.cpp -o DataRetriveFromIntelBuffer16
//DataRetriveFromIntelBuffer16.exe 0010603_NVM.HEX 36 51 16
//Expected out as follows:
//36
//01000A006400E803E803000100000100
