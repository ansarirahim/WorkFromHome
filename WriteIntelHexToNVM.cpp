#include <cstring>
#include <iostream>


#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "iosfwd"
#include <iostream>
#include <iostream>
#include "SimpleGPIO_SPI.h"
#include "SPI_SS_Def.H"
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//#include <spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
using std::cout;
using std::endl;

int main(int argc, char **argv)
{

///////////////////
BYTE pages128[128];
int ret = 0;
	int fd;
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 100000; //need to be speeded up when working
static uint16_t delay = 5;
fd = open("/dev/spidev1.0", O_RDWR); //open the spi device
	if (fd < 0)
		pabort("can't open device");

	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode); //set the spi mode
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode); //get the spi mode (test)
	if (ret == -1)
		pabort("can't get spi mode");

	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits); //set the spi bits per word
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits); //get the spi bits per word (test)
	if (ret == -1)
		pabort("can't get bits per word");

	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed); //set the spi max speed
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed); //get the spi max speed (test)
	if (ret == -1)
		pabort("can't get max speed hz");

	puts("");
	printf("The spi mode is set to: %d\n", mode); //output successful settings to the terminal
	printf("Bits per word: %d\n", bits);
	speed = 10000;
	printf("Max speed is set to: %d Hz (%d KHz) (%d MHz)\n", speed, speed / 1000, speed / 1000000);

////////////////
BYTE yed=80;
//////////CRC//
char addressmid=0;
char addresslow=0;
char addresshigh=0;
for(unsigned int i=0;i<vPageDetails.size();i++)
 {
//printf("\n%.2X %.2X\n",vPageDetails.at(i).extendedLinearAdderess,vPageDetails.at(i).pageNo);

//////////////////////////////////
for (int page128=0;page128<2;page128++){
addresshigh =vPageDetails.at(i).extendedLinearAdderess;// Spi_address >> 16; //
			addressmid = vPageDetails.at(i).pageNo;//Spi_address >> 8;	 //
			addresslow = 0;//Spi_address;
			///printf("\nWriting..Adress=%.2X %.2X%.2X, Adress=%ld",addresshigh, addressmid,addresslow,Spi_address );
			char writeenable[1] = {
				WREN,
			};
if(page128)
addresslow=128;
else
addresslow=0;
			char writecommand[3] = {
				WRITE,
//				addresshigh,
				addressmid,
				addresslow,
			};
printf("\n\nAdre-%.2X %.2X %.2X\n",vPageDetails.at(i).pageNo,addressmid,addresslow);
for( int m=0;m<128;m++)
{pages128[m]=vPageDetails.at(i).pageData[m+addresslow];

printf("%.2X",pages128[m]);
if(m%16==0)
printf("\n");
}

			///setcharbuffer(TemCharBuffer,256,set);

			struct spi_ioc_transfer message[1] = {
				0,
			}; //setup spi transfer data structure

			message[0].tx_buf = (unsigned long)writeenable; //send the write enable command
			message[0].rx_buf = (unsigned long)NULL;
			message[0].len = sizeof(writeenable);
			message[0].cs_change = 0;
			//chip select needs to be released
			usleep(500);
			//////gpio_set_value_spi(SS6, LOW);
			ret = ioctl(fd, SPI_IOC_MESSAGE(1), &message); //spi check if sent
			if (ret < 1)
				pabort("can't send spi message");
			///////////////////////////////////////////////////////
			struct spi_ioc_transfer message1[2] = {
				0,
			}; //setup spi transfer data structure

			message1[0].tx_buf = (unsigned long)writecommand; //send the write command and address
			message1[0].rx_buf = (unsigned long)NULL;
			message1[0].len = sizeof(writecommand);
			message1[0].cs_change = 0;
			message1[1].tx_buf = (unsigned long)pages128;//vPageDetails.at(i).pageData;//
			; //data;//TempByteBuffer;//data;         //send the data
			message1[1].rx_buf = (unsigned long)NULL;
			message1[1].len =128;//256;// sizeof(vPageDetails.at(i).pageData); //data);//TempByteBuffer);
			message1[1].cs_change = 0;;							//release the chip select line
			usleep(5000);

			ret = ioctl(fd, SPI_IOC_MESSAGE(2), &message1); //spi check if sent
			if (ret < 1)
				pabort("can't send spi message");
			usleep(50000);

////////////////////////////////////
  /* for(int k=0;k<256;k++)
{
if(k%16==0)
printf("\n");
printf("%.2X",vPageDetails.at(i).pageData[k]);
}*/ 
   //yed = getNVM_CRC(vPageDetails.at(i).pageData, 256, yed);  
 }
}
close(fd);
// printf("\n\nCRC41 of Data=0x%.2X i=%d linceCounter=%u exc=%u pgc=%u\n",yed,vPageDetails.size(),lineCounter,lc,pageCounter);

 ///
// printf("\nfileData Size=%u",fileData.size());
// vPageDetails.shrink_to_fit();
//  printf("\nExtLA=%u PC=%u,vPageDetails=%u", lc, pageCounter,vPageDetails.size());

//  //printf("\n");
 


//  for(unsigned int i=0;i<vPageDetails.size();i++)
//  {
//      if((requestedELA==vPageDetails.at(i).extendedLinearAdderess)&& (vPageDetails.at(i).pageNo==requestedPageNo)){
//    printf("\n")  ;
// printf("%.2X%.2X",vPageDetails.at(i).extendedLinearAdderess,vPageDetails.at(i).pageNo);
// for(int k=fromIndex;k<toIndex;k++)
// {
//     if(k%16==0)
// printf("\n");
//      printf("%.2X",vPageDetails.at(i).pageData[k]);
    
    
   
// }

// }
     
//  }
// for(int i=fromIndex;i<=toIndex;i++){
// if(i%16==0)
// printf("\n");
// printf("%.2X",tempPageData[i]);
// }
//     for(int k=0;k<1;k++){
// for(int j=0 ;j<1;j++)
//     for(int pg=0;pg<256;pg++){
//      printf("%.2X",vExtendedLinearDetails.at(k).vPageDetails.at(j).pageData[pg]);
//      if(pg%16==0)
//      printf("\n");
//                         }

//     }
}
