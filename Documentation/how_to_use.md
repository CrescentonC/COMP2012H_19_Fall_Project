# Graphical Programming and Visualized Debugging Platform
##### COMP2012H project
-----------------------

## Documentation(3/3)
- How to use the visualizer


## How to use the visualizer
----------------------------------
1. ### Intro to layout
    Open the Window, there are 4 regions: "block choice area", "show define area", "button area", "canvas area" in counter-clockwise direction


2. ### Define Variable
    in the "block choice area", choose "Def Var" button, in the pop out window user will give a unique variable name, then variable type (6 types total) and initial value,
    after that a new  lable appears on the "show define area"
    right click it, you can choose to see its details and delete it

3. ### Use built in Functions
    on the "block choice area", click an operator, i.e. "and",
    then input two source variable names, and the destination variable name
    the new label's background color become red because some of its operands are not set properly
    left click and drag it so that it can move on the canvas
    right click and a context menu will appear that one can delete it / see the details and change the attributes

    (NOTE: built in function buttons have different operands which can be found when used)
    (NOTE: IF and WHILE has one step deeper than the normal function buttons and only accept user defined functions at there T/F deeper layer)


4. ### Define user-defined functions
    click "Def Func" button in the "block choice area", a pop out window will ask you to fill in a unique function name, then parameter ammount, and each parameter type
    After definition, a Label with the function name defined just now will appear on the "show define area". (i.e. we create function a(bool, bool))
    Left click the label (i.e. click button a), an "instantiated" label will show on the "canvas area" with pop up windows asking for operands. It's pretty similar to the built in functions when use
    Right click the label one can choose edit function, the canvas area will be refreshed to "your selected function" 's function body, user can define the function body in the same way, the dark blue color indicates which function is being edited
    After finish the definition, user right click "main" function label can choose edit can go back to the main function with main's canvas freshed out
    (Note: it should be able to support recursion as the recursion runs perfectly at individual backend test)
    

5. ### Logic connection
    The function is connected using wires and each function start with a "start" label
    Find "Start Point" button in the "block choice area", click it and a "start" label will appear on the "canvas area", that's the start point of the function
    Click the Wire button, release, and move the mouse to an emtpy place at canvas area
    click once, move mouse and click second time. A line with green start and red end will appear on the canvas representing the logic connection and direction. Left click and drag and right click delete. Move the line with green end on the start and the other end on another operating block label.
    (NOTE: directly click on the block label doesn't work as the left click on the label regarded as drag move the label)

6.  ###Run
    After finish connecting the logic (i.e. START->PRINT(int))
    one click the run button (at the backend the program will analyze the program)
    another big window will jump out.
    On left down corner there are three buttons, providing close the window, step run and all-finish
    The "All Variables", "Running Flow" and "Program Output" will show the corresponding contents.