#include <snes.h>

extern char patterns, patterns_end;
extern char palette, palette_end;
extern char map, map_end;

extern char bg2_tiles, bg2_tiles_end;
extern char bg2_p, bg2_p_end;
extern char bg2_m, bg2_m_end;

extern char sprites_tiles, sprites_tiles_end;
extern char sprites_p, sprites_p_end;

extern const unsigned char hdmaGradientList[];

u8 pada,padb;
u16 pad0;

u16 y;

#define BG1 0
#define BG2 1
#define BG3 2
#define BG4 3

#define VRAM_MAP_OFFSET_BG1 0x7400
#define VRAM_MAP_OFFSET_BG2 0x7800
#define VRAM_TILES_OFFSET_BG1 0x0000
#define VRAM_TILES_OFFSET_BG2 0x1000
#define VRAM_TILES_OFFSET_SPRITES 0x4000

//---------------------------------------------------------------------------------
int main(void)
{

	bgInitMapSet(BG2, &bg2_m, (&bg2_m_end - &bg2_m), SC_32x32, VRAM_MAP_OFFSET_BG2);
	bgInitTileSet(BG2, &bg2_tiles, &bg2_p, 1, (&bg2_tiles_end - &bg2_tiles), (&bg2_p_end - &bg2_p), BG_16COLORS, VRAM_TILES_OFFSET_BG2);	
	
	oamInitGfxSet(&sprites_tiles, (&sprites_tiles_end - &sprites_tiles), &sprites_p, (&sprites_p_end - &sprites_p), 0, VRAM_TILES_OFFSET_SPRITES, OBJ_SIZE16_L32);
		
    // Now Put in 16 color mode and disable other BGs except 1st one
    setMode(BG_MODE1, 0);
    bgSetDisable(1);
    bgSetEnable(BG2);
    setScreenOn();

	oamSetEx(0*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(2*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(3*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(4*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(5*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(6*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(7*4, OBJ_LARGE, OBJ_SHOW);
	
	y = 0;
	
	// Initialize the gradient color effect 
	setModeHdmaColor((u8 *) &hdmaGradientList);
	pada=0; padb=0;
	
    // Wait for nothing :P
    while (1)
    {
		
		oamSet(0*4, 0, y, 3, 0, 0, 0x00, 0);
		oamSet(1*4, 1*32, y, 3, 0, 0, 0x00, 1);
		oamSet(2*4, 2*32, y, 3, 0, 0, 0x00, 2);
		oamSet(3*4, 3*32, y, 3, 0, 0, 0x00, 3);
		oamSet(4*4, 4*32, y, 3, 0, 0, 0x00, 4);
		oamSet(5*4, 5*32, y, 3, 0, 0, 0x00, 5);
		oamSet(6*4, 6*32, y, 3, 0, 0, 0x00, 6);
		oamSet(7*4, 7*32, y, 3, 0, 0, 0x00, 7);
	
		y++;
        // Get current #0 pad
        pad0 = padsCurrent(0);

		// remove it with key a
		if (pad0 & KEY_A) {
			if (!pada) {
				pada=1;
				setModeHdmaReset(0x00);
			}
		}
		else pada=0;
		
		// put it again with key b
		if (pad0 & KEY_B) {
			padb=1;
			setModeHdmaColor((u8 *) &hdmaGradientList);
		}
		else padb=0;

		// Wait vblank sync
        WaitForVBlank();
    }
    return 0;
}