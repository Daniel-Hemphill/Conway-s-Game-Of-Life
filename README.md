# Conway's Game of Life with WxWidgets

This repository contains a miniature demo of Conway's Game of Life implemented using WxWidgets.

## Prerequisites

Before running the code, make sure you have WxWidgets installed on your system.

## Running the Game of Life Demo

1. Clone this repository to your local machine.
2. Compile the code using the appropriate compiler for your system and link against WxWidgets.

## Demo Overview

The code provided gives a basic demonstration of Conway's Game of Life using WxWidgets. The Game of Life is a cellular automaton devised by mathematician John Conway. It consists of a grid of cells that evolve based on simple rules:

- Any live cell with fewer than two live neighbors dies, as if by underpopulation.
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies, as if by overpopulation.
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
