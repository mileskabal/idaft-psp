#include <oslib/oslib.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <pspaudio_kernel.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("idaft", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

// TWILIGHT ZONE! <do doo do doo>
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
}
// END OF TWILIGHT ZONE! <do doo do do> 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init OSLib:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int initOSLib(){
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
	oslInitAudioME(OSL_FMT_MP3);
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    int skip = 0;

    initOSLib();
	oslIntraFontInit(INTRAFONT_CACHE_MED);
	
	OSL_IMAGE *background, *idaft, *concept, *pspport, *playonline, *help, *lowbtn, *highbtn, *high2btn, *pausebtn, *playbtn, *lrbtn, *btnup, *btndown;
	
	background = oslLoadImageFilePNG ("data/back.png", OSL_IN_RAM,OSL_PF_8888);
	idaft = oslLoadImageFilePNG ("data/idaft.png", OSL_IN_RAM,OSL_PF_8888);
	concept = oslLoadImageFilePNG ("data/concept.png", OSL_IN_RAM,OSL_PF_8888);
	pspport = oslLoadImageFilePNG ("data/pspport.png", OSL_IN_RAM,OSL_PF_8888);
	playonline = oslLoadImageFilePNG ("data/playonline.png", OSL_IN_RAM,OSL_PF_8888);
	help = oslLoadImageFilePNG ("data/help.png", OSL_IN_RAM,OSL_PF_8888);
	lowbtn = oslLoadImageFilePNG ("data/low.png", OSL_IN_RAM,OSL_PF_8888);
	highbtn = oslLoadImageFilePNG ("data/high.png", OSL_IN_RAM,OSL_PF_8888);
	high2btn = oslLoadImageFilePNG ("data/high2.png", OSL_IN_RAM,OSL_PF_8888);
	pausebtn = oslLoadImageFilePNG ("data/pause.png", OSL_IN_RAM,OSL_PF_8888);
	playbtn = oslLoadImageFilePNG ("data/play.png", OSL_IN_RAM,OSL_PF_8888);
	lrbtn = oslLoadImageFilePNG ("data/lr.png", OSL_IN_RAM,OSL_PF_8888);
	btnup = oslLoadImageFilePNG ("data/btn_up.png", OSL_IN_RAM,OSL_PF_8888);
	btndown = oslLoadImageFilePNG ("data/btn_down.png", OSL_IN_RAM,OSL_PF_8888);
	
	OSL_FONT *pgfFont = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont, 0.75, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
    oslSetFont(pgfFont);
	
	OSL_SOUND *son1, *son2, *son3, *son4, *son5, *son6, *son7, *son8, *son9, *son10, *son11, *son12, *son13, *son14, *son15, *son16, *sonhigh1, *sonhigh2, *sonhigh3, *sonhigh4, *sonhigh5, *sonhigh6, *sonhigh7, *sonhigh8, *sonhigh9, *sonhigh10, *sonhigh11, *sonhigh12, *sonhigh13, *sonhigh14, *sonhigh15, *sonhigh16, *sonhi1, *sonhi2, *sonhi3, *sonhi4, *sonhi5, *sonhi6, *sonhi7, *sonhi8, *instru; 
	
	instru = oslLoadSoundFileMP3("data/beat.idf",OSL_FMT_STREAM);
	
	son1 = oslLoadSoundFileWAV("data/Over1.idf",OSL_FMT_NONE); //Over
	son2 = oslLoadSoundFileWAV("data/WorkIs1.idf",OSL_FMT_NONE); //Work is
	son3 = oslLoadSoundFileWAV("data/After1.idf",OSL_FMT_NONE); //After
	son4 = oslLoadSoundFileWAV("data/Ever1.idf",OSL_FMT_NONE); //Ever
	son5 = oslLoadSoundFileWAV("data/Never1.idf",OSL_FMT_NONE); //Never
	son6 = oslLoadSoundFileWAV("data/Our1.idf",OSL_FMT_NONE); //Our
	son7 = oslLoadSoundFileWAV("data/Hour1.idf",OSL_FMT_NONE); //Hour
	son8 = oslLoadSoundFileWAV("data/MoreThan1.idf",OSL_FMT_NONE); //More than
	son9 = oslLoadSoundFileWAV("data/Stronger1.idf",OSL_FMT_NONE); // Stronger
	son10 = oslLoadSoundFileWAV("data/Faster1.idf",OSL_FMT_NONE); //Faster
	son11 = oslLoadSoundFileWAV("data/Better1.idf",OSL_FMT_NONE); //Better
	son12 = oslLoadSoundFileWAV("data/Harder1.idf",OSL_FMT_NONE); //Harder
	son13 = oslLoadSoundFileWAV("data/MakesUs1.idf",OSL_FMT_NONE); //Make us
	son14 = oslLoadSoundFileWAV("data/DoIt1.idf",OSL_FMT_NONE); // Do it
	son15 = oslLoadSoundFileWAV("data/MakeIt1.idf",OSL_FMT_NONE); //Make it
	son16 = oslLoadSoundFileWAV("data/WorkIt1.idf",OSL_FMT_NONE); //Work it

	sonhigh1 = oslLoadSoundFileWAV("data/Over2.idf",OSL_FMT_NONE); //Over
	sonhigh2 = oslLoadSoundFileWAV("data/WorkIs2.idf",OSL_FMT_NONE); //Work is
	sonhigh3 = oslLoadSoundFileWAV("data/After2.idf",OSL_FMT_NONE); //After
	sonhigh4 = oslLoadSoundFileWAV("data/Ever2.idf",OSL_FMT_NONE); //Ever
	sonhigh5 = oslLoadSoundFileWAV("data/Never2.idf",OSL_FMT_NONE); //Never
	sonhigh6 = oslLoadSoundFileWAV("data/Our2.idf",OSL_FMT_NONE); //Our
	sonhigh7 = oslLoadSoundFileWAV("data/Hour2.idf",OSL_FMT_NONE); //Hour
	sonhigh8 = oslLoadSoundFileWAV("data/MoreThan2.idf",OSL_FMT_NONE); //More than
	sonhigh9 = oslLoadSoundFileWAV("data/Stronger2.idf",OSL_FMT_NONE); // Stronger
	sonhigh10 = oslLoadSoundFileWAV("data/Faster2.idf",OSL_FMT_NONE); //Faster
	sonhigh11 = oslLoadSoundFileWAV("data/Better2.idf",OSL_FMT_NONE); //Better
	sonhigh12 = oslLoadSoundFileWAV("data/Harder2.idf",OSL_FMT_NONE); //Harder
	sonhigh13 = oslLoadSoundFileWAV("data/MakesUs2.idf",OSL_FMT_NONE); //Make us
	sonhigh14 = oslLoadSoundFileWAV("data/DoIt2.idf",OSL_FMT_NONE); // Do it
	sonhigh15 = oslLoadSoundFileWAV("data/MakeIt2.idf",OSL_FMT_NONE); //Make it
	sonhigh16 = oslLoadSoundFileWAV("data/WorkIt2.idf",OSL_FMT_NONE); //Work it
	
	sonhi1 = oslLoadSoundFileWAV("data/Over3.idf",OSL_FMT_NONE); //Over
	sonhi2 = oslLoadSoundFileWAV("data/WorkIs3.idf",OSL_FMT_NONE); //Work is
	sonhi3 = oslLoadSoundFileWAV("data/After3.idf",OSL_FMT_NONE); //After
	sonhi4 = oslLoadSoundFileWAV("data/Ever3.idf",OSL_FMT_NONE); //Ever
	sonhi5 = oslLoadSoundFileWAV("data/Never3.idf",OSL_FMT_NONE); //Never
	sonhi6 = oslLoadSoundFileWAV("data/Our3.idf",OSL_FMT_NONE); //Our
	sonhi7 = oslLoadSoundFileWAV("data/Hour3.idf",OSL_FMT_NONE); //Hour
	sonhi8 = oslLoadSoundFileWAV("data/MoreThan3.idf",OSL_FMT_NONE); //More than
	
	int jeu = 0;
	int dejajeu = 0;
	int i;
	
	
	int dureefinal = 20;
	int dureecourant = 0;
	
	int high = 0;
	int playinstru = 0;
	int playbeat = 0;
	
	int caseClignote = 17;
	int courantClignote = 0;
	int vitesseClignote = 10;
	int nbrCase = 16;
	int caseWidth = 57;
	int caseHeight = 63;
	int hautX = 105;
	int basX = 180;
	
	int casePosX[16][4];
	
	casePosX[0][0] = 1;
	casePosX[0][1] = 1+caseWidth;
	casePosX[0][2] = hautX;
	casePosX[0][3] = hautX+caseHeight;
	
	casePosX[1][0] = 61;
	casePosX[1][1] = 61+caseWidth;
	casePosX[1][2] = hautX;
	casePosX[1][3] = hautX+caseHeight;
	
	casePosX[2][0] = 121;
	casePosX[2][1] = 121+caseWidth;
	casePosX[2][2] = hautX;
	casePosX[2][3] = hautX+caseHeight;
	
	casePosX[3][0] = 181;
	casePosX[3][1] = 181+caseWidth;
	casePosX[3][2] = hautX;
	casePosX[3][3] = hautX+caseHeight;
	
	casePosX[4][0] = 241;
	casePosX[4][1] = 241+caseWidth;
	casePosX[4][2] = hautX;
	casePosX[4][3] = hautX+caseHeight;
	
	casePosX[5][0] = 301;
	casePosX[5][1] = 301+caseWidth;
	casePosX[5][2] = hautX;
	casePosX[5][3] = hautX+caseHeight;
	
	casePosX[6][0] = 361;
	casePosX[6][1] = 361+caseWidth;
	casePosX[6][2] = hautX;
	casePosX[6][3] = hautX+caseHeight;
	
	casePosX[7][0] = 421;
	casePosX[7][1] = 421+caseWidth;
	casePosX[7][2] = hautX;
	casePosX[7][3] = hautX+caseHeight;
	
	casePosX[8][0] = 1;
	casePosX[8][1] = 1+caseWidth;
	casePosX[8][2] = basX;
	casePosX[8][3] = basX+caseHeight;
	
	casePosX[9][0] = 61;
	casePosX[9][1] = 61+caseWidth;
	casePosX[9][2] = basX;
	casePosX[9][3] = basX+caseHeight;
	
	casePosX[10][0] = 121;
	casePosX[10][1] = 121+caseWidth;
	casePosX[10][2] = basX;
	casePosX[10][3] = basX+caseHeight;
	
	casePosX[11][0] = 181;
	casePosX[11][1] = 181+caseWidth;
	casePosX[11][2] = basX;
	casePosX[11][3] = basX+caseHeight;
	
	casePosX[12][0] = 241;
	casePosX[12][1] = 241+caseWidth;
	casePosX[12][2] = basX;
	casePosX[12][3] = basX+caseHeight;
	
	casePosX[13][0] = 301;
	casePosX[13][1] = 301+caseWidth;
	casePosX[13][2] = basX;
	casePosX[13][3] = basX+caseHeight;
	
	casePosX[14][0] = 361;
	casePosX[14][1] = 361+caseWidth;
	casePosX[14][2] = basX;
	casePosX[14][3] = basX+caseHeight;
	
	casePosX[15][0] = 421;
	casePosX[15][1] = 421+caseWidth;
	casePosX[15][2] = basX;
	casePosX[15][3] = basX+caseHeight;
	
	
	int idaftX = 0;
	int idaftY = 0;
	int idaftPosX = 240;
	int idaftPosY = 35;
	
	int conceptX = 0;
	int conceptY = 0;
	int conceptPosX = 240;
	int conceptPosY = 100;
	
	int pspportX = 0;
	int pspportY = 0;
	int pspportPosX = 240;
	int pspportPosY = 150;
	
	int playonlineX = 0;
	int playonlineY = 0;
	int playonlinePosX = 240;
	int playonlinePosY = 200;
   
    while(!osl_quit){
		
        if (!skip){
            
			// DEBUT JEU
			if(jeu){
			
				oslStartDrawing();
				oslReadKeys(); 
				oslDrawImage(background);
				
				if(dureecourant < dureefinal){
					idaftY = ceil((700/dureefinal)*dureecourant/10);
					idaftX = ceil((1640/dureefinal)*dureecourant/10);
					idaftPosX = ceil(240-(idaftX/2));
					idaftPosY = ceil((70-idaftY)/2);
					dureecourant++;
				}
				else{
					idaftX = 164;
					idaftY = 70;
					idaftPosX = ceil(240-(idaftX/2));
					idaftPosY = 0;
				}
				
				
				idaft->stretchX = idaftX;
				idaft->stretchY = idaftY;
				idaft->x = idaftPosX;
				idaft->y = idaftPosY;
				oslDrawImage(idaft);
				
				// oslSetFont(policeArial);
				// oslPrintColorShadow(2, 20,JAUNE,"X", 0);
				// oslPrintColorShadow(2, 30,JAUNE,"Y", 0);
				
				//TECHNOLOGIC
				/*
				if(osl_keys->analogX > 30 || osl_keys->analogX < -30){
					if(!osl_audioActive[1])
					oslPlaySound(technologic, 1);
				}
				*/
				if (osl_keys->pressed.circle){
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh1, 7);
						}
						else if(high == 2){
						oslPlaySound(sonhi1, 7);
						}
						else{
						oslPlaySound(son1, 7);
						}
						caseClignote = 15;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh9, 7);
						}
						else{
							if(high != 2){
							oslPlaySound(son9, 7);
							}
						}
						caseClignote = 7;
						//dureecourant = 0;
					}
				}
				
				if (osl_keys->pressed.cross){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh2, 5);
						}
						else if(high == 2){
						oslPlaySound(sonhi2, 5);
						}
						else{
						oslPlaySound(son2, 5);
						}
						caseClignote = 14;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh10, 5);
						}
						else{
						if(high != 2){
						oslPlaySound(son10, 5);
						}
						}
						caseClignote = 6;
					}
				}
				
				if (osl_keys->pressed.square){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh3, 6);
						}
						else if(high == 2){
						oslPlaySound(sonhi3, 6);
						}
						else{
						oslPlaySound(son3, 6);
						}
						caseClignote = 13;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh11, 6);
						}
						else{
						if(high != 2){
						oslPlaySound(son11, 6);
						}
						}
						caseClignote = 5;
					}
				}
				
				if (osl_keys->pressed.triangle){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh4, 5);
						}
						else if(high == 2){
						oslPlaySound(sonhi4, 5);
						}
						else{
						oslPlaySound(son4, 5);
						}
						caseClignote = 12;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh12, 5);
						}
						else{
						if(high != 2){
						oslPlaySound(son12, 5);
						
						}
						}
						caseClignote = 4;
					}
				}
				
				if (osl_keys->pressed.right){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh5, 4);
						}
						else if(high == 2){
						oslPlaySound(sonhi5, 4);
						}
						else{
						oslPlaySound(son5, 4);
						}
						caseClignote = 11;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh13, 4);
						}
						else{
						if(high != 2){
						oslPlaySound(son13, 4);
						}
						}
						caseClignote = 3;
				}
				}
				
				if (osl_keys->pressed.down){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh6, 2);
						}
						else if(high == 2){
						oslPlaySound(sonhi6, 2);
						}
						else{
						oslPlaySound(son6, 2);
						}
						caseClignote = 10;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh14, 2);
						}
						else{
						if(high != 2){
						oslPlaySound(son14, 2);
						}
						}
						caseClignote = 2;
					}
				}
				
				if (osl_keys->pressed.left){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh7, 3);
						}
						else if(high == 2){
						oslPlaySound(sonhi7, 3);
						}
						else{
						oslPlaySound(son7, 3);
						}
						caseClignote = 9;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh15, 3);
						}
						else{
						if(high != 2){
						oslPlaySound(son15, 3);
						}
						}
						caseClignote = 1;
					}
				}
				
				if (osl_keys->pressed.up){ 
					if (osl_keys->pressed.L || osl_keys->pressed.R || osl_keys->held.L || osl_keys->held.R ){
						if(high == 1){
						oslPlaySound(sonhigh8, 2);
						}
						else if(high == 2){
						oslPlaySound(sonhi8, 2);
						}
						else{
						oslPlaySound(son8, 2);
						}
						caseClignote = 8;
					}
					else{
						if(high == 1){
						oslPlaySound(sonhigh16, 2);
						}
						else{
						if(high != 2){
						oslPlaySound(son16, 2);
						}
						}
						caseClignote = 0;
					}
				}
				
				if (osl_keys->pressed.select && !osl_keys->pressed.start){ 
					if(!playinstru){
						oslPlaySound(instru, 1);
						playinstru = 1;
					}
					else{
						oslPauseSound(instru, -1);
						if(!osl_audioActive[1]){
						playinstru = 0;
						}
					}
					
					if(playbeat){
						playbeat = 0;
					}
					else{
						playbeat = 1;
					}
				}
				if (osl_keys->pressed.start && !osl_keys->pressed.select){ 
					if(high < 2){
						high++;
					}
					else{
						high = 0;
					}
				}
				if(osl_keys->pressed.L){
					if(osl_keys->held.R){
					jeu = 0;
					dureecourant = 0;
					dejajeu = 1;
					}
				}
				if(osl_keys->pressed.R){
					if(osl_keys->held.L){
					jeu = 0;
					dureecourant = 0;
					dejajeu = 1;
					}
				}
				
				
				for(i = 0; i < nbrCase;i++){
					if(high == 2){
						if(caseClignote < 8){
						caseClignote = 17;
						}
					}
					if(i == caseClignote){
					oslDrawFillRect(casePosX[i][0],casePosX[i][2],casePosX[i][1],casePosX[i][3],RGBA(0, 255, 0,255));
					}
					else{
						if(i<8 && high==2){
							oslDrawFillRect(casePosX[i][0],casePosX[i][2],casePosX[i][1],casePosX[i][3],RGBA(0, 45, 0,255));
							oslDrawRect(casePosX[i][0],casePosX[i][2],casePosX[i][1],casePosX[i][3],RGBA(0,84,0,255));
						}
						else{
							oslDrawFillRect(casePosX[i][0],casePosX[i][2],casePosX[i][1],casePosX[i][3],RGBA(0, 84, 0,255));
							oslDrawRect(casePosX[i][0],casePosX[i][2],casePosX[i][1],casePosX[i][3],RGBA(0,255,0,255));
						}
					}
					
				}
				
				
				if(caseClignote != 17){			
					if(courantClignote > vitesseClignote){
					courantClignote++;
					}
					else{
					caseClignote = 17;
					courantClignote = 0;
					}
				}
				
				
				oslDrawFillRect(2,250,118,269,RGBA(0, 84, 0,255));
				oslDrawRect(2,250,118,269,RGBA(0,255,0,255));
				
				oslDrawFillRect(122,250,238,269,RGBA(0, 84, 0,255));
				oslDrawRect(122,250,238,269,RGBA(0,255,0,255));
				
				oslDrawFillRect(242,250,318,269,RGBA(0, 84, 0,255));
				oslDrawFillRect(322,250,398,269,RGBA(0, 84, 0,255));
				oslDrawFillRect(402,250,478,269,RGBA(0, 84, 0,255));
				
				if(high == 0){
				oslDrawRect(242,250,318,269,RGBA(0,255,0,255));
				}
				if(high == 1){
				oslDrawRect(322,250,398,269,RGBA(0,255,0,255));
				}
				if(high == 2){
				oslDrawRect(402,250,478,269,RGBA(0,255,0,255));
				}
				
				if(high != 2){
					oslDrawImageXY(btnup,0,105);
				}
				oslDrawImageXY(btndown,0,175);
				
				if(playbeat){
					oslDrawImageXY(pausebtn,2,251);
				}
				else{
					oslDrawImageXY(playbtn,2,251);
				}
				
				oslDrawImageXY(lrbtn,128,251);
				oslDrawImageXY(lowbtn,244,251);
				oslDrawImageXY(highbtn,324,251);
				oslDrawImageXY(high2btn,404,251);
			
			}//FIN JEU
			//DEBUT SPLASH
			else{
				oslStartDrawing();
				oslReadKeys(); 
				oslDrawFillRect(0,0,480,272,RGBA(0, 0, 0,255));
				
				if(dureecourant < dureefinal){
					idaftY = ceil((700/dureefinal)*dureecourant/10);
					idaftX = ceil((1640/dureefinal)*dureecourant/10);
					idaftPosX = ceil(240-(idaftX/2));
					idaftPosY = ceil((70-idaftY)/2);
					
					conceptY = ceil((410/dureefinal)*dureecourant/10);
					conceptX = ceil((1280/dureefinal)*dureecourant/10);
					conceptPosX = ceil(240-(conceptX/2));
					conceptPosY = ceil((41-conceptY)/2+100);
					
					pspportY = ceil((420/dureefinal)*dureecourant/10);
					pspportX = ceil((630/dureefinal)*dureecourant/10);
					pspportPosX = ceil(240-(pspportX/2));
					pspportPosY = ceil((42-pspportY)/2+150);
					
					playonlineY = ceil((430/dureefinal)*dureecourant/10);
					playonlineX = ceil((1450/dureefinal)*dureecourant/10);
					playonlinePosX = ceil(240-(playonlineX/2));
					playonlinePosY = ceil((43-playonlineY)/2+200);
					
					dureecourant++;
				}
				else{
					idaftX = 164;
					idaftY = 70;
					idaftPosX = ceil(240-(idaftX/2));
					idaftPosY = 0;
					
					conceptX = 128;
					conceptY = 41;
					conceptPosX = ceil(240-(conceptX/2));
					conceptPosY = 100;
					
					pspportX = 63;
					pspportY = 42;
					pspportPosX = ceil(240-(pspportX/2));
					pspportPosY = 150;
					
					playonlineX = 145;
					playonlineY = 43;
					playonlinePosX = ceil(240-(playonlineX/2));
					playonlinePosY = 200;
				}
				
				if(conceptPosY==100 && dejajeu==1){
				oslDrawImageXY(help,0,242);
				}
				
				idaft->stretchX = idaftX;
				idaft->stretchY = idaftY;
				idaft->x = idaftPosX;
				idaft->y = idaftPosY;
				oslDrawImage(idaft);
				
				concept->stretchX = conceptX;
				concept->stretchY = conceptY;
				concept->x = conceptPosX;
				concept->y = conceptPosY;
				oslDrawImage(concept);
				
				pspport->stretchX = pspportX;
				pspport->stretchY = pspportY;
				pspport->x = pspportPosX;
				pspport->y = pspportPosY;
				oslDrawImage(pspport);
				
				playonline->stretchX = playonlineX;
				playonline->stretchY = playonlineY;
				playonline->x = playonlinePosX;
				playonline->y = playonlinePosY;
				oslDrawImage(playonline);
				
				
				
				if (osl_keys->pressed.start){ 
					jeu = 1;
					dureecourant = 0;
					high=0;
				}
				
			}//FIN SPLASH
			
			
			
			oslEndFrame();
	        skip = oslSyncFrame();
        }
		
    }
	
    //Quit OSL:
    oslEndGfx();

    sceKernelExitGame();
    return 0;

}
