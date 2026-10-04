ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME by following this guide: https://github.com/alekmaul/pvsneslib/wiki/Installation")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := colors

all: bitmaps $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx

bg2.pic: bg2.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 128 -u 128 -e 1 -p -t png -m -i $<

sprites.pic: sprites.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -p -o 128 -s 8 -R -i $<
	
bitmaps : bg2.pic sprites.pic


