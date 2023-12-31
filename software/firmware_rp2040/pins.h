// Configuration Section

// Define the pins for the rows and columns
const int ROW_PINS[] = {D0, D1, D2, D3};
const int COL_PINS[] = {D8, D7};
const int NUM_ROWS = sizeof(ROW_PINS) / sizeof(ROW_PINS[0]);
const int NUM_COLS = sizeof(COL_PINS) / sizeof(COL_PINS[0]);

// Define pins for the rotary encoder(s)
const int ROT_A = D10;
const int ROT_B = D9;
const int ROT_CLK = D6;

// Define the shortcuts
const int NUM_SHORTCUTS = 28;
const char* shortcutNames[] = {"undo", "copy", "paste", "view", "pipette", "ui tog", "redo", "snap left", "snap right", "search", "task view", 
                                "lasso", "steady", "fill", "fit view", "brushes", "move", "thick +", "thick -", "command", "comment","uncomment",
                                "save","split", "view face", "view all", "fullscreen", "minimize"};
const char shortcutCombos[NUM_SHORTCUTS][3] = {
  {KEY_LEFT_CTRL, 'z'},
  {KEY_LEFT_CTRL, 'c'},
  {KEY_LEFT_CTRL, 'v'},
  {KEY_LEFT_CTRL, '8'},
  {KEY_LEFT_ALT, 'i'},
  {'t'},
  {KEY_LEFT_CTRL, 'y'},
  {KEY_LEFT_GUI, KEY_LEFT_ARROW},
  {KEY_LEFT_GUI, KEY_RIGHT_ARROW},
  {KEY_LEFT_GUI, '1'},
  {KEY_LEFT_GUI, KEY_TAB},
  {'l'},
  {KEY_LEFT_CTRL, 'r'},
  {KEY_LEFT_CTRL, 'f'},
  {KEY_LEFT_CTRL, '0'},
  {KEY_LEFT_CTRL, 'b'},
  {' '},
  {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'k'},
  {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'l'},
  {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'p'},
  {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'k'},
  {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'l'},
  {KEY_LEFT_CTRL, 's'},
  {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'q'},
  {KEY_LEFT_CTRL, '8'},
  {KEY_LEFT_CTRL, '7'},
  {KEY_F11},
	{KEY_LEFT_GUI, 'm'}
};

const int NUM_KEYBIND_SETS = 4; // Change the value according to your requirements

// Define the keybinds
const char* keybinds[NUM_KEYBIND_SETS][NUM_ROWS][NUM_COLS] = {
  {{"undo", "snap left"},
   {"redo", "snap right"},
   {"fullscreen", "search"},
   {"minimize", "task view"}},
  
  {{"undo", "steady"},
   {"redo", "fit view"},
   {"ui tog", "brushes"},
   {"thick -", "thick +"}},
  
  {{"comment", "command"},
   {"uncomment", "undo"},
   {"split", "snap left"},
   {"save", "snap right"}},

  {{"undo", "view all"},
   {"task view", "view face"},
   {"split", "snap left"},
   {"save", "snap right"}}
};

        