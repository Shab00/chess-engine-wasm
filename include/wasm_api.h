#ifndef WASM_API_H
#define WASM_API_H

#ifdef __cplusplus
extern "C" {
#endif

void wasm_engine_new_game(void);

int wasm_engine_set_fen(const char *fen);

int wasm_engine_make_move(const char *move_str);

int wasm_engine_get_bestmove(char *move_str_out, int buflen);

void wasm_engine_get_fen(char *fen_out, int buflen);

#ifdef __cplusplus
}
#endif

#endif 
