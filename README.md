# ♟️ Top Chess Players Manager

A C++ program to manage and sort professional chess player data using dynamic memory allocation and class-based design. Created for **CMPE241 Project**.

## Features

- Add, edit, and delete player records
- Load and save data from/to text files
- Sort players by name, surname, rating, ranking, nationality, birth year or FIDE ID
- Prevent duplicate FIDE IDs
- Clean formatted table display with borders
- Input validation for both strings and numbers
- Dynamically expanding array structure

## Data Structure

Each player includes:
- Name
- Surname
- Nationality
- Ranking
- Rating
- Birth Year
- FIDE ID

All players are stored in a dynamically allocated array of `Player` objects.

## Files

- `top_chess_players.cpp` – Main source file

##  Usage

1. **Compile the project**:

```bash
g++ top_chess_players.cpp -o chess
