import streamlit as st

def main():
    st.title("Macroboard Configuration")

    # Row and Column Pins
    st.header("Pins Configuration")
    row_pins = st.text_input("Row Pins (comma-separated)", value="D0,D1,D2,D3")
    col_pins = st.text_input("Column Pins (comma-separated)", value="D8,D7")

    # Number of Rows and Columns
    st.header("Matrix Size")
    num_rows = st.number_input("Number of Rows", value=4, min_value=1, step=1)
    num_cols = st.number_input("Number of Columns", value=2, min_value=1, step=1)

    # Shortcuts Configuration
    st.header("Shortcuts Configuration")
    num_shortcuts = st.number_input("Number of Shortcuts", value=3, min_value=1, step=1)
    shortcut_names = []
    shortcut_combos = []
    for i in range(num_shortcuts):
        name = st.text_input(f"Shortcut Name {i+1}")
        combo = st.text_input(f"Shortcut Combo {i+1}")
        shortcut_names.append(name)
        shortcut_combos.append(combo)

    # Keybinds Configuration
    st.header("Keybinds Configuration")
    keybinds = []
    for i in range(num_rows):
        row_keybinds = []
        for j in range(num_cols):
            keybind = st.selectbox(f"Row {i+1}, Column {j+1} Keybind", shortcut_names)
            row_keybinds.append(keybind)
        keybinds.append(row_keybinds)

    # Export and Import
    if st.button("Export Configuration"):
        export_configuration(row_pins, col_pins, num_rows, num_cols, num_shortcuts, shortcut_names, shortcut_combos, keybinds)
    
    uploaded_file = st.file_uploader("Import Configuration", type="h")
    if uploaded_file is not None:
        imported_data = uploaded_file.getvalue().decode("utf-8")
        parse_imported_data(imported_data)

def export_configuration(row_pins, col_pins, num_rows, num_cols, num_shortcuts, shortcut_names, shortcut_combos, keybinds):
    # Generate the pins.h file content
    content = f"// Define the pins for the rows and columns\n"
    content += f"const int ROW_PINS[] = {{{row_pins}}};\n"
    content += f"const int COL_PINS[] = {{{col_pins}}};\n"
    content += f"const int NUM_ROWS = {num_rows};\n"
    content += f"const int NUM_COLS = {num_cols};\n\n"

    # Generate the shortcuts section
    content += f"// Define the shortcuts\n"
    content += f"const int NUM_SHORTCUTS = {num_shortcuts};\n"
    content += "const char* shortcutNames[] = {"
    for i, name in enumerate(shortcut_names):
        content += f'"{name}"'
        if i < num_shortcuts - 1:
            content += ", "
    content += "};\n"
    content += "const char shortcutCombos[NUM_SHORTCUTS][2] = {"
    for i, combo in enumerate(shortcut_combos):
        content += "{" + ",".join(combo) + "}"
        if i < num_shortcuts - 1:
            content += ", "
    content += "};\n\n"

    # Generate the keybinds section
    content += "// Define the keybinds\n"
    content += "const char* keybinds[NUM_ROWS][NUM_COLS] = {"
    for i, row in enumerate(keybinds):
        content += "{"
        for j, keybind in enumerate(row):
            content += f'"{keybind}"'
            if j < num_cols - 1:
                content += ", "
        content += "}"
        if i < num_rows - 1:
            content += ", "
    content += "};\n"

    # Save the content to a file
    with open("pins.h", "w") as file:
        file.write(content)

    st.success("Configuration exported successfully!")

def parse_imported_data(data):
    # Split the imported data into sections
    sections = data.split("//")

    # Extract the pins configuration
    pins_section = sections[1].strip().split("\n")
    row_pins = pins_section[0].split("=")[1].strip().strip("{};")
    col_pins = pins_section[1].split("=")[1].strip().strip("{};")
    num_rows = int(pins_section[2].split("=")[1].strip().strip(";"))
    num_cols = int(pins_section[3].split("=")[1].strip().strip(";"))

    # Extract the shortcuts configuration
    shortcuts_section = sections[2].strip().split("\n")
    num_shortcuts = int(shortcuts_section[0].split("=")[1].strip().strip(";"))
    shortcut_names = [name.strip().strip('"') for name in shortcuts_section[1].split("=")[1].strip().strip("{};").split(",")]
    shortcut_combos = [[char.strip().strip("'") for char in combo.strip().strip("{}").split(",")] for combo in shortcuts_section[2].split("=")[1].strip().strip("{};").split(",")]

    # Extract the keybinds configuration
    keybinds_section = sections[3].strip().split("\n")
    keybinds = [[bind.strip().strip('"') for bind in row.strip().strip("{}").split(",")] for row in keybinds_section[1:]]

    # Display the imported configuration
    st.success("Configuration imported successfully!")
    st.write("Row Pins:", row_pins)
    st.write("Column Pins:", col_pins)
    st.write("Number of Rows:", num_rows)
    st.write("Number of Columns:", num_cols)
    st.write("Number of Shortcuts:", num_shortcuts)
    st.write("Shortcut Names:", shortcut_names)
    st.write("Shortcut Combos:", shortcut_combos)
    st.write("Keybinds:", keybinds)

if __name__ == "__main__":
    main()
