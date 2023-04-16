#include"BotPlayer.h"

#include <iostream>

    // This is the BotPlayer class. It has an algorithm to calculate the best move based on relative board positions.

    // It essentially checks for priority moves, and otherwise places moves that maximises it's board value,

    // linking different twos and threes and valuable and reducing the next players board position is valuable as well.



    // This is the override method for the getMove function.

int BotPlayer::get_move() {

	// The priority of actions is first to check if can win this turn.

	// checkForWin returns the winning column if possible, and -1 if not.

	int thisPlayerWinColumn = 	this->checkForWin ( token );

	if ( thisPlayerWinColumn >= 0 ) {

	    return thisPlayerWinColumn;
	}


	// Next check to see if the nextPlayer can win can win this turn.

	int nextPlayerWinColumn = checkForWin ( opponent_token );

	if ( nextPlayerWinColumn >= 0 ) {

	    return nextPlayerWinColumn;
	}


	// Then check if a two move win is on

	int thisPlayerTwoMoveWinColumn = checkForThisPlayerTwoMoveWin ();

	if ( thisPlayerTwoMoveWinColumn >= 0 ) {

	    return thisPlayerTwoMoveWinColumn;
	}


	// and final priority move is to check whether the next player can win in two moves.

	int nextPlayerTwoMoveWinColumn = checkForNextPlayerTwoMoveWin ();

	if ( nextPlayerTwoMoveWinColumn >= 0 ) {

	    return nextPlayerTwoMoveWinColumn;
	}


	// after this the relative value of each move is calculated and the best column return here.


return getBestRelativeMoveColumnValue ( token )[0];
}


    // The getWinCountWinningColumn method returns a 2 digit array with the number of wins in

    // position 0, and a winning column or -1 in position 1.

    // Having this method made the initial getMove method look a bit neater.


int BotPlayer::checkForWin ( char given_token ) {

	std::array<int,2> nextPlayerWinCountAndWinningColumn = getWinCountWinningColumn  ( given_token );

	int nextPlayerNumPossibleWins = nextPlayerWinCountAndWinningColumn[0];

	int nextPlayerWinningColumn = nextPlayerWinCountAndWinningColumn[1];

	if ( nextPlayerNumPossibleWins > 0 ) {

	    return nextPlayerWinningColumn;
	}

	return -1;
}


    // There are separate methods for the two win move, as for this player it's no good

    // if it allows the next player to win.

    // The method works by placing a token in each column, if they're empty, and counting how

    // many winning moves there are. If there's 2 or more, and it wont set the next player up

    // for a win, it'll return that column. Otherwise it'll return -1.


int BotPlayer::checkForThisPlayerTwoMoveWin() {

	for ( int column = 0; column < board_width; column++ ) {

	    if ( game_board_pointer->check_column_is_full ( column ) == true ) {

		continue;
	    }

	    else {

		game_board_pointer->make_move( token, column);

		// The [0] position of the getWinCountWinningColumn is an integer of the win count.

		int thisPlayerNextTurnNumWins = getWinCountWinningColumn( token )[0];

		int nextPlayerNextTurnNumWins = getWinCountWinningColumn  ( opponent_token )[0];


		if ( thisPlayerNextTurnNumWins >= 2 && nextPlayerNextTurnNumWins < 1 ) {

            game_board_pointer->undo_move(column);

		    return column;
		}

		game_board_pointer->undo_move(column);

		continue;
	    }
	}

	return -1;
    }


    // This one is very similar but doesn't have the condition of allowing a win.

int BotPlayer::checkForNextPlayerTwoMoveWin () {

	for ( int column = 0; column < board_width; column++ ) {

	    if ( game_board_pointer->check_column_is_full( column ) == true ) {

		continue;
	    }

	    else {

		game_board_pointer->make_move( opponent_token, column);

		int nextPlayerNextTurnNumWins = getWinCountWinningColumn( opponent_token)[0];

		if ( nextPlayerNextTurnNumWins >= 2 ) {

		    game_board_pointer->undo_move(column);

		    game_board_pointer->make_move( token, column);

		    // This is here so it won't block a potential two move win, that might be missed,

		    // and create an opportunity for a one turn win.

		    int nextPlayerPotentialWins = getWinCountWinningColumn  ( opponent_token )[0];

		    if ( nextPlayerPotentialWins < 1 ) {

			game_board_pointer->undo_move(column);

			return column;
		    }
		}

		game_board_pointer->undo_move(column);

		continue;
	    }
	}

	return -1;
    }



    //This gets the Integer array of WinCount and winning column that was mentioned previously.

std::array<int,2> BotPlayer::getWinCountWinningColumn ( char given_token) {

	int winCount = 0;

	int winningColumn = -1;

	// We don't ever want to place a token in a full column. It isn't a problem to place it,

	// as it just won't change anything, but the following removeToken call will then take

	// the top row of game tokens off.

	for ( int column = 0; column < board_width; column++ ) {

	    if ( game_board_pointer->check_column_is_full( column ) == true ) {

		continue;
	    }

	    else {

		// For each column, place a token and see if it's a winner. Keep count of how many are.

		int move_position = game_board_pointer->make_move( given_token, column);

		if ( game_board_pointer->check_for_win(given_token, move_position) == true ) {

		    winCount = winCount + 1;

		    // We only need one winning column so it just records the latest witnessed.

		    winningColumn = column;
		}

		game_board_pointer->undo_move(column);

		continue;
	    }
	}

	std::array<int,2> winCountWinningColumn = { winCount, winningColumn };

	return winCountWinningColumn;
    }



    // After checking for priority moves the bot then gets the move that would give it

    // the best relative board position. This method checks each column and returns the best one.

    // It returns a 2D array with position [0] the column and [1] the value. This helped as sometimes different ones

    // are needed and it prevented it needing to be counted twice.


std::array<int,2> BotPlayer::getBestRelativeMoveColumnValue (char given_token) {

	int bestRelativeBoardValue =  ( -5 * winValue * winValue );

	int bestColumn = 0;

	for (int column = 0; column < board_width; column++) {

	    if ( game_board_pointer->check_column_is_full ( column ) == true ) {
		continue;
	    }

	    else {

		int relativeBoardValue = getRelativeMoveValue ( given_token , column );

		if ( relativeBoardValue > bestRelativeBoardValue) {

		    bestRelativeBoardValue = relativeBoardValue;

		    bestColumn = column;
		}

		else {
		    continue;
		}
	    }
	}

	std::array<int,2> bestRelativeMoveColumnValue = { bestColumn, bestRelativeBoardValue };

	return bestRelativeMoveColumnValue;
    }



    // This is where the bulk of the processing happens for how good a move is.


int BotPlayer::getRelativeMoveValue (char given_token, int given_column) {

	// We don't want choosing a full column to ever be a good idea.

	if ( game_board_pointer->check_column_is_full ( given_column ) == true ) {

	    return - ( winValue * winValue);
	}

	else {

	    // if it's available, place a token and see how the board looks.

	    game_board_pointer->make_move( given_token, given_column);

	    int nextPlayerWinCount = getWinCountWinningColumn( opponent_token )[0];  //SUSPECT HERE ******************************

	    int thisPlayerWinCount = getWinCountWinningColumn( given_token )[0];


	    // if the next player can win, it's a very bad turn. But not as bad as a full column.

	    if ( nextPlayerWinCount >= 1 ) {

		game_board_pointer->undo_move(given_column);

		return winValue * ( -10 );
	    }


	    // if this player can win in two moves it's a very good turn.

	    if ( thisPlayerWinCount >= 2 ) {

		game_board_pointer->undo_move(given_column);

		return winValue * ( 10 );
	    }


	    if ( nextPlayerWinCount >= 2 ) {

		game_board_pointer->undo_move(given_column);

		return winValue * ( -5 );
	    }


	    int relativeTurnValue = 0;

	    int thisPlayerTotalPotentialBoardValue = 0;

	    int nextPlayerTotalPotentialBoardValue = 0;

	    int columnCount = 0;


	    // if going here means this player can win next turn, assume the next player will place their token in that column,

	    // and then calculate the best position that can be played off from there.

	    // The getBestRelativeMoveColumnValue() call is recursive as this method is called in that one.

	    if ( thisPlayerWinCount >= 1 ) {

		int thisPlayerNextTurnWinColumn = getWinCountWinningColumn( token )[1];

		game_board_pointer->make_move( opponent_token, thisPlayerNextTurnWinColumn);

		relativeTurnValue = getBestRelativeMoveColumnValue( token )[1];

		game_board_pointer->undo_move( thisPlayerNextTurnWinColumn );

		game_board_pointer->undo_move( given_column );

		return relativeTurnValue;

	    }

	    // otherwise if there isn't a winning move that the player will block,

	    // try placing the nextPlayers token in each column and seeing what the board looks like for them.

	    //SUSPECT HERE *********************************
	    else{
            for ( int column = 0 ; column < board_width; column++ ) {

            if ( game_board_pointer->check_column_is_full( column ) == true ) {
                continue;
            }

		    // We don't want to set them up for a 2 move win.
		    game_board_pointer->make_move( opponent_token, column);

		    int nextPlayer2ndMoveWinCount = getWinCountWinningColumn( opponent_token )[0];

		    if ( nextPlayer2ndMoveWinCount >= 2 ) {

			game_board_pointer->undo_move(column);

			game_board_pointer->undo_move(given_column);

			return winValue * ( -5 );
		    }

		    // If no wins are on then the relative board value is calculated by comparing the board value of this player if they go there,

		    // with the average of the next players move subtracted from it. This means setting up the next player for a good move,

		    // is processed as a bad idea. Alternatively the bot is just optimising board value and it's chances to win until there

		    // is one available it can go for.

		    thisPlayerTotalPotentialBoardValue = thisPlayerTotalPotentialBoardValue + game_board_pointer->get_player_board_values( player_number );

		    nextPlayerTotalPotentialBoardValue =  nextPlayerTotalPotentialBoardValue + game_board_pointer->get_player_board_values( opponent_number );

		    columnCount = columnCount + 1;

		    game_board_pointer->undo_move(column);

		    continue;
		}
	    }

	    // This is here as we don't ever want to divide by 0, this shouldn't get called as then the game would be a draw.

	    if ( columnCount > 0 ) {

		relativeTurnValue = ( thisPlayerTotalPotentialBoardValue ) - ( nextPlayerTotalPotentialBoardValue / 10 ) / columnCount;
	    }

	    // I added a / 2 to the next player potential board value so the bot favours making moves itself.

	    else {

		relativeTurnValue = ( thisPlayerTotalPotentialBoardValue ) - ( nextPlayerTotalPotentialBoardValue / 2 );
	    }

	    game_board_pointer->undo_move(given_column);

	    return relativeTurnValue;
	}

}


/*
int BotPlayer::get_move() {


    int move_position = 99;

    bool this_player_won = false;
    bool opponent_won = false;

    std::array<int, 2> board_values = {0,0};

    int relative_value = -9000;
    int best_relative_value = -9000;
    int best_column = -1;

    bool column_full = false;
    bool potential_win = true;
//
    int this_player_value;
    int opponent_value;

    for(int column_number = 0; column_number < this->board_width; column_number++){
    relative_value = 0;
    column_full = false;
    potential_win = false;
        //std::cout << "For column: " << column_number << std::endl;


        column_full = game_board_pointer->check_column_is_full(column_number);
        if( column_full ){

            //std::cout << "Column is full: " << column_number << std::endl;
            relative_value = -8000;
            continue;}


        move_position = game_board_pointer->make_move(this->token, column_number);

        this_player_won = game_board_pointer->check_for_win(this->token, move_position);
        if (this_player_won){
            game_board_pointer->undo_move(column_number);
            //std::cout << "This player will win: " << column_number << std::endl;
            return column_number;
            }

        potential_win = this->check_for_potential_win(opponent_token);
        if( potential_win ){
            relative_value = -7000;
            //game_board_pointer->undo_move(column_number);
            //std::cout << "Oppenent will win: " << column_number << std::endl;
            }

        else{

            board_values = game_board_pointer->get_board_values();

            int this_player_value = board_values[player_number];

            int opponent_value = board_values[opponent_number];

            relative_value = this_player_value - 1.2*opponent_value;

            //std::cout << "this player value is: " << this_player_value <<std::endl;

            //std::cout << "opponent_value is: " << opponent_value <<std::endl;

        }

            //std::cout << "relative value is: " << relative_value <<std::endl;

            if (relative_value > best_relative_value){

                best_column = column_number;
                best_relative_value = relative_value;

                //std::cout << "best_column: " << best_column <<std::endl;
                //std::cout << "best_relative_value: " << best_relative_value <<std::endl;
            }

            game_board_pointer->undo_move(column_number);
        }
    //std::cout << "best_column_is: " << best_column << " because relative value is" << best_relative_value <<std::endl;

return best_column;
}

bool BotPlayer::check_for_potential_win(char check_token){

    bool can_win = false;

    bool column_full = false;

    int move_position = 99;

    for(int column = 0; column < board_width; column++){

        column_full = false;

        column_full = game_board_pointer->check_column_is_full(column);

        if(column_full){
            continue;
        }

        move_position = game_board_pointer->make_move(check_token, column);
        can_win = game_board_pointer->check_for_win(check_token, move_position);

        if (can_win){
        game_board_pointer->undo_move(column);
        return can_win;
        }

        game_board_pointer->undo_move(column);
    }
    return can_win;
}

*/
