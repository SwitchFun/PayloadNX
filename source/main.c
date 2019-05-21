#include <string.h>
#include <stdio.h>
#include <switch.h>
#define IRAM_PAYLOAD_MAX_SIZE 0x2F000
#define IRAM_PAYLOAD_BASE 0x40010000
static alignas(0x1000) u8 g_reboot_payload[IRAM_PAYLOAD_MAX_SIZE];
static alignas(0x1000) u8 g_ff_page[0x1000];
static alignas(0x1000) u8 g_work_page[0x1000];
int isClose;
void do_iram_dram_copy(void *buf, uintptr_t iram_addr, size_t size, int option) {
    memcpy(g_work_page, buf, size);
    SecmonArgs args = {0};
    args.X[0] = 0xF0000201;             /* smcAmsIramCopy */
    args.X[1] = (uintptr_t)g_work_page;  /* DRAM Address */
    args.X[2] = iram_addr;              /* IRAM Address */
    args.X[3] = size;                   /* Copy size */
    args.X[4] = option;                 /* 0 = Read, 1 = Write */
    svcCallSecureMonitor(&args);
    memcpy(buf, g_work_page, size);
}
void copy_to_iram(uintptr_t iram_addr, void *buf, size_t size) {
    do_iram_dram_copy(buf, iram_addr, size, 1);
}
void copy_from_iram(void *buf, uintptr_t iram_addr, size_t size) {
    do_iram_dram_copy(buf, iram_addr, size, 0);
}
static void clear_iram(void) {
    memset(g_ff_page, 0xFF, sizeof(g_ff_page));
    for (size_t i = 0; i < IRAM_PAYLOAD_MAX_SIZE; i += sizeof(g_ff_page)) {
        copy_to_iram(IRAM_PAYLOAD_BASE + i, g_ff_page, sizeof(g_ff_page));
    }
	
}
static void reboot_to_payload(void) {
    clear_iram();
    
    for (size_t i = 0; i < IRAM_PAYLOAD_MAX_SIZE; i += 0x1000) {
        copy_to_iram(IRAM_PAYLOAD_BASE + i, &g_reboot_payload[i], 0x1000);
    }
    
    splSetConfig((SplConfigItem)65001, 2);
}


void sxosMagic(){
	
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
        printf("SPL could not be initalized, Please message on our discord.\n");
        
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/sx.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
	
	
}
}

void atmosphereCheck(){
	bool isAtmosphere = 0;
	Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
		//loader.ini = atmosphere only
        FILE *f = fopen("sdmc:/atmosphere/loader.ini", "rb");
        if (f == NULL) {
            FuseeMagic();
            
        } else {
            fclose(f);
			consoleClear();
            printf("Atmosphere Detected! PayloadNX does NOT Support Plain-Atmosphere \n Please use Hekate or other CFW.");
        }
	
	
}
}

void reiCheck(){
	bool isAtmosphere = 0;
	Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
		//loader.ini = atmosphere only
        FILE *f = fopen("sdmc:/atmosphere/loader.ini", "rb");
        if (f == NULL) {
            ReiNXMagic();
            
        } else {
            fclose(f);
			consoleClear();
            printf("Atmosphere Detected! PayloadNX does NOT Support Plain-Atmosphere \n Please use Hekate or other CFW.");
        }
	
	
}
}


void sxCheck(){
	bool isAtmosphere = 0;
	Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
		//loader.ini = atmosphere only
        FILE *f = fopen("sdmc:/atmosphere/loader.ini", "rb");
        if (f == NULL) {
            sxosMagic();
            
        } else {
            fclose(f);
			consoleClear();
            printf("Atmosphere Detected! PayloadNX does NOT Support Plain-Atmosphere \n Please use Hekate or other CFW.");
        }
	
	
}
}

void hekateMagic(){
	
		
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/hekate.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
	
	
}
}
void ReiNXMagic(){
	
		
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/ReiNX.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
		
}
}
void FuseeMagic(){
	
		
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
        printf("SPL could not be initalized, Please message on our discord.\n");
        
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/fusee-primary.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
	
	
}
	
}

void ArgonNXMagic(){
	
		
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
        printf("SPL could not be initalized, Please message on our discord.\n");
        
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/argon-nx.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
	
	
}
	
}
void Slot1Magic(){
	
		
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
        printf("SPL could not be initalized, Please message on our discord.\n");
        
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/slot1.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
	
	
}
	
}

void Slot2Magic(){
	
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
        printf("SPL could not be initalized, Please message on our discord.\n");
        
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/slot2.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
            
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
}
}
void ArgonCheck(){
	bool isAtmosphere = 0;
	Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
		//loader.ini = atmosphere only
        FILE *f = fopen("sdmc:/atmosphere/loader.ini", "rb");
        if (f == NULL) {
            ArgonNXMagic();
            
        } else {
            fclose(f);
			consoleClear();
            printf("Atmosphere Detected! PayloadNX does NOT Support Plain-Atmosphere \n Please use Hekate or other CFW.");
        }
}
}

void hekateCheck(){
	bool isAtmosphere = 0;
	Result rc = splInitialize();
    if (R_FAILED(rc)) {
		printf("SPL could not be initalized, Please message on our discord.\n");
    } else {
		//loader.ini = atmosphere only
        FILE *f = fopen("sdmc:/atmosphere/loader.ini", "rb");
        if (f == NULL) {
            hekateMagic();
            
        } else {
            fclose(f);
			consoleClear();
            printf("Atmosphere Detected! PayloadNX does NOT Support Plain-Atmosphere \n Please use Hekate or other CFW.");
        }
}
}

void Slot3Magic(){
    Result rc = splInitialize();
    if (R_FAILED(rc)) {
        printf("SPL could not be initalized, Please message on our discord.\n");
        
    } else {
        FILE *f = fopen("sdmc:/PayloadNX/slot3.bin", "rb");
        if (f == NULL) {
            ExceptionNotFound();
        } else {
            fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
            fclose(f);
            printf("Rebooting to payload...");
			reboot_to_payload();
        }
	
	
}
}
void ExceptionNotFound(){
	consoleClear();
	printf("PayloadNX can not find the Payload!\n");
	printf("Press B to exit.");
	int isClose = true;
	
}
void confirmAtmosphereBoot(){
	consoleClear();
	printf("Atmosphere is reported to NOT work with PayloadNX (BOOT-FROM), are you sure?\n Press (A) To Continue.\n Press (B) to exit.");
	int confirmAtmosphere = 1;
	int confirmed = 0;
}
int main(int argc, char **argv)
{
    consoleInit(NULL);
	bool isDev = 1;
	int confirmAtmosphere = 0;
	int menu1 = 6;
	int menu3 = 8;
	int menu4 = 7;
	int menu5 = 9;
	int menu6 = 10;
	int menu7 = 11;
	int menu8 = 12;
	int menu9 = 13;
	int current = 6;
	printf("\x1b[1;1H%s%s%s", CONSOLE_BLUE, "PayloadNX 2.0.2", CONSOLE_RESET);
	printf("\x1b[2;1H%s%s%s", CONSOLE_GREEN, "--Installed Custom Firmwares--", CONSOLE_RESET);
	    Result rc1 = splInitialize();
    if (R_FAILED(rc1)) {
        printf("\n ERROR: Please restart PayloadNX!\n");
        
    } else {
        FILE *f = fopen("sdmc:/boot.dat", "rb");
        if (f == NULL) {
           printf("\x1b[3;1H%s%s%s", CONSOLE_RED, "SXOS: Not Installed", CONSOLE_RESET);
            
        } else {
            fclose(f);
            printf("\x1b[3;1H%s%s%s", CONSOLE_RED, "SXOS: Installed", CONSOLE_RESET);
			
        }
	
	
	}
    Result rc2 = splInitialize();
    if (R_FAILED(rc2)) {
        
        printf("\n ERROR: Please restart PayloadNX!\n");
        
    } else {
        FILE *f = fopen("sdmc:/ReiNX/splash.bin", "rb");
        if (f == NULL) {
			printf("\x1b[4;1H%s%s%s", CONSOLE_CYAN, "ReiNX: Not Installed\n", CONSOLE_RESET);
		   
            printf("\n");
        } else {
            fclose(f);
            printf("\x1b[4;1H%s%s%s", CONSOLE_CYAN, "ReiNX: Installed", CONSOLE_RESET);
			printf("\n");
        }
	
	
}

	
	printf("\n\n\n\n\n");
	printf(CONSOLE_GREEN);
	printf("\n\x1b[6;4HSXOS");
	printf(CONSOLE_YELLOW);
	printf("\x1b[8;4HAtmosphere Fusee");
	printf(CONSOLE_RED);
	printf("\x1b[7;4HHekate");
	printf(CONSOLE_GREEN);
	printf("\x1b[9;4HReiNX");
	printf(CONSOLE_WHITE);
	printf("\x1b[10;4HArgonNX\n");
	printf(CONSOLE_RED);
	printf("\x1b[11;4HSLOT #1");
	printf(CONSOLE_CYAN);
	printf("\x1b[12;4HSLOT #2");
	printf(CONSOLE_YELLOW);
	printf("\x1b[13;4HSLOT #3");

	printf("\x1b[%d;2H>", current);
    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		
		if (kDown & KEY_UP) 
		{
			printf("\x1b[%d;2H ", current);
			current = current - 1;
			if (current < 6) current = 13;
				printf ("\n");
			    printf ("\x1b[%d;2H>", current);		
			}

			if (kDown & KEY_DOWN) {
				printf("\x1b[%d;2H ", current);
			current = current + 1; 
			if (current > 13) current = 6;
				printf("\n");
				printf("\x1b[%d;2H>", current);
		}
		if (kDown & KEY_A) 
		{
			if (current == menu1) sxCheck();
		}

		if (kDown & KEY_A) 
		{
			if (current == menu3) atmosphereCheck();
		}
		
		if (kDown & KEY_A) 
		{
			if (current == menu4) hekateCheck();
		}
		if (kDown & KEY_A) 
		{
			if (current == menu5) reiCheck();
		}
		if (kDown & KEY_A){
			if (current == menu6) ArgonCheck();
		}
				if (kDown & KEY_A){
			if (current == menu7) Slot1Magic();
		}
		/*if(confirmed == 1){
			FuseeMagic();
		}
		*/
		if (kDown & KEY_A){
			if (current == menu8) Slot2Magic();
		}
		if (kDown & KEY_A){
			if (current == menu9) Slot3Magic();
		}
		if (kDown & KEY_B){
			break;
		}
		if (kDown & KEY_A){
			if (isClose == 1){
				break;
			}
		}
		consoleUpdate(NULL);
	
	}

    consoleExit(NULL);
    return 0;
}
