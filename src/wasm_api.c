#include <string.h>
#include <stdio.h>
#include "position.h"
#include "movegen.h"
#include "search.h"
#include "wasm_api.h"

static Position g_position;
static int last_a1 = -999;

static int compute_fun_depth(const Position *pos, int color) {
    int base_depth = 2;
    int knight_count = 0, bishop_count = 0, rook_count = 0, queen_count = 0;
    for (int i = 0; i < 64; ++i) {
        int p = pos->board[i];
        int abs_p = (p < 0) ? -p : p;
        if ((color == COLOR_WHITE && p > 0) || (color == COLOR_BLACK && p < 0)) {
            switch (abs_p) {
                case PIECE_KNIGHT: knight_count++; break;
                case PIECE_BISHOP: bishop_count++; break;
                case PIECE_ROOK:   rook_count++; break;
                case PIECE_QUEEN:  queen_count++; break;
            }
        }
    }
    int missing_knights  = 2 - knight_count;
    int missing_bishops  = 2 - bishop_count;
    int missing_rooks    = 2 - rook_count;
    int missing_queens   = 1 - queen_count;
    int depth = base_depth
        + (missing_knights  * 1)
        + (missing_bishops  * 1)
        + (missing_rooks    * 2)
        + (missing_queens   * 3);
    if (depth < 2) depth = 2;
    if (depth > 8) depth = 8;
    return depth;
}

void wasm_engine_new_game(void) {
    char err[256];
    pos_error_t r = position_from_fen(&g_position,
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        err, sizeof(err));
    last_a1 = -999;
}

int wasm_engine_set_fen(const char *fen) {
    char err[256];
    pos_error_t r = position_from_fen(&g_position, fen, err, sizeof(err));
    return r != POS_OK;
}

static int promo_from_char(char c) {
    switch (c) {
        case 'q': case 'Q': return PIECE_QUEEN;
        case 'r': case 'R': return PIECE_ROOK;
        case 'b': case 'B': return PIECE_BISHOP;
        case 'n': case 'N': return PIECE_KNIGHT;
        default:  return PIECE_EMPTY;
    }
}

int wasm_engine_make_move(const char *move_str) {
    if (!move_str || strlen(move_str) < 4) return 1;
    int from = position_square_from_coords(move_str[0], move_str[1]);
    int to   = position_square_from_coords(move_str[2], move_str[3]);
    if (from == POS_NO_SQUARE || to == POS_NO_SQUARE) return 1;
    int promo = PIECE_EMPTY;
    if (strlen(move_str) >= 5) promo = promo_from_char(move_str[4]);

    MoveUndo mv_undo;
    make_move(&g_position, from, to, promo, &mv_undo);

    return 0;
}

static void format_move(int from, int to, int promo, char *buf, int bufsz) {
    char fbuf[3], tbuf[3];
    position_square_to_coords(from, fbuf, sizeof(fbuf));
    position_square_to_coords(to, tbuf, sizeof(tbuf));
    char pc = 0;
    switch (promo) {
        case PIECE_KNIGHT: pc = 'n'; break;
        case PIECE_BISHOP: pc = 'b'; break;
        case PIECE_ROOK:   pc = 'r'; break;
        case PIECE_QUEEN:  pc = 'q'; break;
    }
    if (pc) {
        snprintf(buf, bufsz, "%s%s%c", fbuf, tbuf, pc);
    } else {
        snprintf(buf, bufsz, "%s%s", fbuf, tbuf);
    }
}

int wasm_engine_get_bestmove(char *move_str_out, int buflen) {
    int depth = compute_fun_depth(&g_position, g_position.side_to_move);
    int best_from = -1, best_to = -1, best_promo = 0;
    int found = search_root(&g_position, depth, &best_from, &best_to, &best_promo, NULL);
    if (found > 0 && best_from >= 0) {
        format_move(best_from, best_to, best_promo, move_str_out, buflen);
        return 0;
    } else {
        if (buflen > 0) move_str_out[0] = 0;
        return 1;
    }
}

void wasm_engine_get_fen(char *fen_out, int buflen) {
    position_to_fen(&g_position, fen_out, buflen);
}
