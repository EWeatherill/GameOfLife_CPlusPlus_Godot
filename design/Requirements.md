# Requirements

## Game properties
101. The game should have 4 states:
    1. start: before evolution has begun the grid contains just dead cells and cells can be toggled between alive and dead
    1. evolving: the grid progresses through generations until there are no more alive cells or the grid state has not changed from the previous generation
    1. paused: the evolution progress is paused
    1. end: evolution has ended
1. Grid cells should be be a fixed size.
1. The grid size should fill the game screen in the start state (before evolution begins).
1. The grid size should not change once evolution has started.
1. The button region should always be visible below the grid irrespective of game screen size.
1. The notification region should always be visible below the grid irrespective of game screen size.
1. The game should return to the start state in any of the following situations:
    1. if the user clears the grid in the pause state
    1. if the user clears the grid in the end state or selects to start a new grid
1. The game should pause if minimised or loss of focus.

## User interaction
201. The user should be able to toggle which cells are alive/dead before evolution begins.
1. The user should have the option to populate the grid with randomly selected alive cells.
1. The user should be able to choose to completely clear the grid of alive cells in the following circumstances:
    1. if there are alive cells in the start state
    1. if there are alive cells in the pause state
    1. if there are alive cells in the end state

## Non-functional requirements
1. The game should work on Ubuntu 18.04.
1. The game should work on Android 10.
