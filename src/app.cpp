Move findBestMove() {
    int rating;
    return findBestMove(0, rating);
}

Move findBestMove(int depth, int & rating) {
    Vector<Move> moveList;
    Move bestMove;
    int minRating = WINNING_POSITION + 1;
    generateMoveList(moveList);
    if (moveList.isEmpty()) error("No moves available");
    for (Move move : moveList) {
        makeMove(move);
        int moveRating = evaluatePosition(depth + 1);
        if (moveRating < minRating) {
            bestMove = move;
            minRating = moveRating;
        }
        retractMove(move);
    }
    rating = -minRating;
    return bestMove;
}

int evaluatePosition(int depth) {
    if (gameIsOver() || depth >= MAX_DEPTH) {
        return evaluateStaticPosition();
    }
    int rating;
    findBestMove(depth, rating);
    return rating;
}
