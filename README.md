# Student-City-Simulator / Student Quest

## Description
Student City Simulator / Student Quest is a console-based simulation game
developed as a course project for the "Introduction to Programming" course
at the Faculty of Mathematics and Informatics, Sofia University.

This game simulates a student's life during his exam session in Student City, Sofia. 
The player's task is to manage resources like knowledge, money, mental health and energy, 
in order to survive his session and pass all exams.
At the same time the player experiences random events (mostly negative) forcing him
to rely not only on strategy but also on luck. 

## Features
- Turn-based gameplay (45 in-game days)
- Multiple player actions (learning, eating, working, resting, going out)
- Random events affecting the player’s statistics
- Exam system with success calculation
- Three difficulty levels
- Automatic saving and loading of game progress
- ASCII-based user interface

<img width="436" height="476" alt="image" src="https://github.com/user-attachments/assets/a291b669-822d-4d8d-8bc0-d20ef64f2e3f" />

## Gameplay Controls
- The game is fully menu-driven.
- Enter the number corresponding to your chosen action.
- Input validation is implemented to handle invalid entries.

## Main actions include:
- Learn
- Eat
- Work
- Rest
- Go out
- Attend exam (available only on exam days)

## Save System
- Game progress is automatically saved to a file named `save.txt`.
- The game saves after each in-game day and when the player exits.
- Upon winning or losing, the save file is cleared.
- Loading resumes the game from the last saved state.

## Technical Details
- Language: C++
- Standard libraries used:
  - `<iostream>`
  - `<fstream>`
  - `<ctime>`
- Randomness is seeded using the system time.
- The project uses structures to represent game state and player statistics.

## Author
Vladimir Pavlov  
Faculty of Mathematics and Informatics  
Sofia University  
Winter Semester 2025/2026
