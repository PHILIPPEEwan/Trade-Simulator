##
## EPITECH PROJECT, 2025
## Trade Barrier Impact Simulator
## File description:
## Makefile for building the GUI version
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude
DEBUGFLAGS = -g -O0 -DDEBUG
RELEASEFLAGS = -O3
LDFLAGS = -lm

CSFML_CFLAGS = $(shell pkg-config --cflags csfml-graphics \
			   csfml-window csfml-system)
CSFML_LDFLAGS = $(shell pkg-config --libs csfml-graphics \
				csfml-window csfml-system)

GUI_CFLAGS = $(CFLAGS) $(CSFML_CFLAGS) -DGUI_MODE
GUI_LDFLAGS = $(LDFLAGS) $(CSFML_LDFLAGS)

SRCDIR = src
OBJDIR = obj
BINDIR = bin

ANIMATION_SRC = $(SRCDIR)/animation/anim_core.c \
				$(SRCDIR)/animation/anim_arrows.c \
				$(SRCDIR)/animation/anim_impacts.c \
				$(SRCDIR)/animation/anim_timeline.c \
				$(SRCDIR)/animation/anim_render.c \
				$(SRCDIR)/animation/anim_particles.c

CSV_SRC = $(SRCDIR)/csv/csv_parser.c \
		  $(SRCDIR)/csv/csv_loader.c

DATA_SRC = $(SRCDIR)/data/country_mgr.c \
		   $(SRCDIR)/data/product_mgr.c \
		   $(SRCDIR)/data/flow_mgr.c \
		   $(SRCDIR)/data/barrier_mgr.c

ECONOMIC_SRC = $(SRCDIR)/economic/impact_calc.c \
			   $(SRCDIR)/economic/welfare_calc.c \
			   $(SRCDIR)/economic/price_calc.c

GUI_SRC = $(SRCDIR)/gui/gui_core.c \
		  $(SRCDIR)/gui/gui_events.c \
		  $(SRCDIR)/gui/gui_render.c \
		  $(SRCDIR)/gui/gui_panels.c \
		  $(SRCDIR)/gui/gui_tooltip.c

MAIN_SRC = $(SRCDIR)/main/main_gui.c \
		   $(SRCDIR)/main/main_init.c

MAP_SRC = $(SRCDIR)/map/world_map.c \
		  $(SRCDIR)/map/map_render.c \
		  $(SRCDIR)/map/map_coords.c \
		  $(SRCDIR)/map/map_regions.c \
		  $(SRCDIR)/map/map_arrows.c

SCENARIO_SRC = $(SRCDIR)/scenario/scenario_mgr.c \
			   $(SRCDIR)/scenario/scenario_presets.c \
			   $(SRCDIR)/scenario/scenario_events.c

TRADE_SRC = $(SRCDIR)/trade/barrier_calc.c \
			$(SRCDIR)/trade/flow_sim.c

UTILS_SRC = $(SRCDIR)/utils/utils_memory.c \
			$(SRCDIR)/utils/utils_string.c \
			$(SRCDIR)/utils/utils_math.c \
			$(SRCDIR)/utils/utils_io.c

ALL_SRC = $(ANIMATION_SRC) $(CSV_SRC) $(DATA_SRC) \
		  $(ECONOMIC_SRC) $(GUI_SRC) $(MAIN_SRC) \
		  $(MAP_SRC) $(SCENARIO_SRC) $(TRADE_SRC) \
		  $(UTILS_SRC)

GUI_OBJECTS = $(ALL_SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = $(BINDIR)/trade_simulator_gui

all: release

release: GUI_CFLAGS += $(RELEASEFLAGS)
release: directories $(TARGET)

debug: GUI_CFLAGS += $(DEBUGFLAGS)
debug: directories $(TARGET)

directories:
	@mkdir -p $(OBJDIR) $(BINDIR)
	@mkdir -p $(OBJDIR)/animation $(OBJDIR)/csv
	@mkdir -p $(OBJDIR)/data $(OBJDIR)/economic
	@mkdir -p $(OBJDIR)/gui $(OBJDIR)/main
	@mkdir -p $(OBJDIR)/map $(OBJDIR)/scenario
	@mkdir -p $(OBJDIR)/trade $(OBJDIR)/utils

$(TARGET): $(GUI_OBJECTS)
	$(CC) $(GUI_OBJECTS) -o $@ $(GUI_LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | directories
	$(CC) $(GUI_CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

rebuild: clean release

run: release
	./$(TARGET)

.PHONY: all release debug clean rebuild run directories
