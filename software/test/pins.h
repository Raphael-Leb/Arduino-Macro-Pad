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
const int NUM_SHORTCUTS = 6;
const char* shortcutNames[] = {"undo", "copy", "paste", "view", "pipette", "ui tog"};
const char shortcutCombos[NUM_SHORTCUTS][3] = {
  {KEY_LEFT_CTRL, 'z'},
  {KEY_LEFT_CTRL, 'c'},
  {KEY_LEFT_CTRL, 'v'},
  {KEY_LEFT_CTRL, '8'},
  {KEY_LEFT_ALT, 'i'},
  {'t'}
};

const int NUM_KEYBIND_SETS = 3; // Change the value according to your requirements

// Define the keybinds
const char* keybinds[NUM_KEYBIND_SETS][NUM_ROWS][NUM_COLS] = {
  {{"undo", "undo"},
   {"copy", "paste"},
   {"copy", "view"},
   {"pipette", "ui tog"}},
  
  {{"copy", "copy"},
   {"copy", "save as"},
   {"cut", "copy"},
   {"paste", "delete"}},
  
  {{"select all", "undo"},
   {"find", "replace"},
   {"zoom in", "zoom out"},
   {"save", "exit"}}
};
