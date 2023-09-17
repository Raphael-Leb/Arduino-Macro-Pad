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
const int NUM_SHORTCUTS = 3;
const char* shortcutNames[] = {"undo", "copy", "paste"};
const char shortcutCombos[NUM_SHORTCUTS][2] = {
  {KEY_LEFT_CTRL, 'z'},
  {KEY_LEFT_CTRL, 'c'},
  {KEY_LEFT_CTRL, 'v'}
};

// Define the keybinds
const char* keybinds[NUM_ROWS][NUM_COLS] = {
  {"undo", "undo"},
  {"copy", "paste"},
  {"copy", "paste"},
  {"copy", "paste"}
};
