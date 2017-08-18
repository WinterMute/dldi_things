/*---------------------------------------------------------------------------------

	DLDI dumper

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

#include <nds/arm9/dldi.h>
#include <fat.h>


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	consoleDemoInit();
	iprintf("dldi dumper!\n\n");


	if(dldiIsValid(io_dldi_data) && fatInitDefault()) {

		iprintf("%s\n",io_dldi_data->friendlyName);

		char dldi_name[10];
		memset(dldi_name,0,10);
		memcpy(dldi_name,&io_dldi_data->ioInterface.ioType,4);

		strcat(dldi_name,".dldi");

		int dldi_size = io_dldi_data->dldiEnd - io_dldi_data->dldiStart;
		int dldi_bss_size = io_dldi_data->bssEnd - io_dldi_data->bssStart;

		iprintf("dldi size is %d bytes\nbss size is %d bytes\n", dldi_size,dldi_bss_size);

		iprintf("Saving %s, %d bytes.\n", dldi_name, dldi_size);

		FILE *dldi_file = fopen(dldi_name,"wb");

		if (dldi_file != NULL) {
			size_t written = fwrite(io_dldi_data,1,dldi_size,dldi_file);
			fclose(dldi_file);
			if(written != dldi_size) {
				perror("write error:");
			}
		} else {
			iprintf("File create failed!\n");
		}
	} else {

		iprintf("failed to mount FAT!\n");

	}

	iprintf("Press start to exit\n");

	while(1) {
		swiWaitForVBlank();
		scanKeys();
		int pressed = keysDown();
		if(pressed & KEY_START) break;
	}

}
