# Graphical Programming and Visualized Debugging Platform
##### COMP2012H project
-----------------------

## Documentation(2/3)
- Project discription


## Project discription
----------------------------------
    Graphical Programming and Visualized Debugging Platform is similar to scratch at frontend for easier GUI programming, and a logic analyzer at the back end able to run the program step by step with itermediate data storage and showing. It aims to help to analyze difficult logic i.e. recursion and so on.

    In this project, we treat each function, variable, semantic keypoint(i.e. IF, WHILE) as an object block, and blocks can nest each other or themselves to create the logic flow.

### backend
    At the backend, we deal with the function and variable blocks, the main structure class are:
        - Block -> Func_Block
          Block -> template <typename T> Var_Block
    We use Func_Block to contain all types of operations, IF, WHILE and normal type function call, Var_Block support 6 type of variable types bool, int, double, bool*, int*, double*

    14 types of built in operators are built at backend, including print, >, <, +, -, *, /, and so on shown in BuiltInOperators.hpp
    -----------------------------------------------------------------------------
    Note that the backend is implemented perfectly with support to recursion and step run shown at a subfolder named "backend"
    !!!!!!!!!!!!!Please have a look at it, though it does not have gui !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

### frontend
    At the front end, we deal with gui, we mainly use class: Visible_Block and the logic line
    the Visible blk can contains the individual key points
    Also, we implemented 2 windows individually


