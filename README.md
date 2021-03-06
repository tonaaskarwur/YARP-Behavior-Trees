

NOTE: This is a work-in-progress library. Stable Version coming soon.
====
A behavior tree library in `YARP`.




DEPENDENCIES
------------


* [YARP](https://www.yarp.it/)
* [LUA](https://www.lua.org/)
* [Qt5](https://doc.qt.io/)



BT NODES SUPPORT
----------------
**Fallback:** Fallback nodes are used to find and execute the first child that does not fail. A Selector node will return immediately with a status code of success or running when one of its children returns success or running. The children are ticked in order of importance, from `left` to `right`.

**Sequence:** Sequence nodes are used to find and execute the first child that has not yet succeeded. A sequence node will return immediately with a status code of `failure` or `running` when one of its children returns failure or running. The children are ticked in order, from `left` to `right`.

**Parallel:** The parallel node ticks its children in parallel and returns success if `M ≤ N` children return success, it returns failure if `N − M + 1` children return failure, and it returns running otherwise.

**Decorator:** The decorator node manipulates the return status of its child according to the policy defined by the user (e.g. it inverts the success/failure status of the child). In this library the decorators implemented are the two common ones: *Decorator Retry* which retries the execution of a node if this fails; and *Decorator Negation* That inverts the Success/Failure outcome.

**Action:** An Action node performs an action, and returns Success if the action is completed, Failure if it can not be completed and Running if completion is under way.

**Condition:** A Condition node determines if a desired condition `c` has been met. Conditions are technically a subset of the Actions, but are given a separate category and graphical symbol to improve readability of the BT and emphasize the fact that they never return running and do not change any internal states/variables of the BT.

**Nodes with memory:**
There exists the memory version of the Sequence and Fallback node. Memory nodes 
always tick the same child until this returns success or
failure, ignoring its status after that.

## Setup
Download and build the repository
This will create the editor binary at <build-directory>/behavior_tree_editor
Open the editor. A window similar to the following should appear.

![alt tag](https://github.com/miccol/YARP-Behavior-Trees/blob/master/YARPBT.JPG)





## Using the editor
---
### Create a new action in Lua
1) In the Toolbar: Lua Scripts->Create Action Script. A dialog windows will appear.
2) Write the name of your new action node and press OK. This will create a Action<name>.lua file in the executable's folder and the corresping node will apper in the scene.
3) Double click the on new node.
4) Implement the functions init(), tick() and halt().
   
### Create a new condition in Lua
1) In the Toolbar: Lua Scripts->Create Condition Script. A dialog windows will appear.
2) Write the name of your new action node and press OK. This will create a Condition<name>.lua file in the executable's folder and the corresping node will apper in the scene.
3) Implement the functions init() and tick().



### Add a node in the scene
1) Right click on the scene
2) Select the corresponding node


### Run the Behavior Tree
1) Make sure that the tree has a root node.
2) Press the Play <img src="https://github.com/miccol/YARP-Behavior-Trees/blob/master/editor/qt_nodeditor/resources/play.png" width="15" height="15"> button. <br/>
3) Enjoy.
![alt tag](https://github.com/miccol/YARP-Behavior-Trees/blob/master/YARPBTRun.JPG)


## Note for YARP nodes
If you have implemented some nodes as external RFModules you can use them in the Behavior Tree by adding a YARP action/condition in the scene and writing the name of the module in the textfield.
Instructions on how to implement an external Behavior Tree action in YARP avaliable here (link here)


ACKNOWLEDGMENTS
-------
The Behavior Tree core is taken from a fork of https://github.com/miccol/Behavior-Tree </br>
The Behavior Tree editor is a modified version of https://github.com/Eurecat/BehaviorTree.CPP, which is based on https://github.com/paceholder/nodeeditor

LICENSE
-------
The MIT License (MIT)

Copyright (c) 2017-2018 Michele Colledanchise

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
