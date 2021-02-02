#                            -*- mode: org; -*-
#
#+TITLE:         Building the Doxygen help for TrafficSim
#+AUTHOR:               Gyeha Lim Tung Nguyen Mahmoud Gadalla Lac Truong (Sophie Truong)
#+DATE:                     August 2020
#+OPTIONS: author:nil ^:{}
# Copyright (c) 2020 TrafficSim Developers.

* Doxygen
  The HTML documentation of TrafficSim can be built using the Doxygen software.
  Images in the documentation are generated using "dot", a program within the
  graphviz software package.  To build the documentation on the Ubuntu GNU/Linux
  system, for example, the user should install both =doxygen= and =graphviz=
  packages, e.g. by typing in a terminal window:

  + =sudo apt-get install doxygen graphviz=

  The users must ensure they have write
  permission for the directory that Doxygen writes files to.

* Configuration
  The Doygen configuration file, Doxyfile, in the =./doc=
  directory is configured to work with Doxygen versions 1.6.3-1.8.5.

  The Header, Footer, and Stylesheet are generated automatically:

  + =doxygen -w html header.html footer.html customdoxygen.css=

  See: https://www.stack.nl/~dimitri/doxygen/manual/customize.html

* Running Doxygen
  In the =./doc= directory type
  + =doxygen=

  which will generate the =./doc/html= directory
  containing the TrafficSim source code documentation.  Load the =index.html= file
  into a browser, \e.g.\
  + =firefox html/index.