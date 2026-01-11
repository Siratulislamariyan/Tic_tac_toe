// app.js — Tic Tac Toe game logic (Pure JavaScript - fallback from C++ WASM)
// 0 = empty, 1 = X (player), 2 = O (computer)
let board = [];

function el(id){return document.getElementById(id);} 

function reset_board() {
  board = Array(9).fill(0);
}

function get_cell(idx) {
  if (idx < 0 || idx > 8) return -1;
  return board[idx];
}

function check_three(a, b, c) {
  if (board[a] === board[b] && board[b] === board[c] && board[a] !== 0) return board[a];
  return 0;
}

function check_winner() {
  // Check rows
  let w = check_three(0, 1, 2); if (w) return w;
  w = check_three(3, 4, 5); if (w) return w;
  w = check_three(6, 7, 8); if (w) return w;
  // Check columns
  w = check_three(0, 3, 6); if (w) return w;
  w = check_three(1, 4, 7); if (w) return w;
  w = check_three(2, 5, 8); if (w) return w;
  // Check diagonals
  w = check_three(0, 4, 8); if (w) return w;
  w = check_three(2, 4, 6); if (w) return w;
  // Check draw
  for (let i = 0; i < 9; i++) if (board[i] === 0) return 0;
  return 3; // draw
}

function find_winning_move(player) {
  for (let i = 0; i < 9; i++) {
    if (board[i] === 0) {
      board[i] = player;
      let w = check_winner();
      board[i] = 0;
      if (w === player) return i;
    }
  }
  return -1;
}

function player_move(idx) {
  if (idx < 0 || idx > 8) return -1;
  if (board[idx] !== 0) return -1;
  board[idx] = 1;
  return check_winner();
}

function computer_move() {
  if (check_winner()) return -1;
  // Win if possible
  let mv = find_winning_move(2);
  if (mv !== -1) { board[mv] = 2; return check_winner(); }
  // Block player
  mv = find_winning_move(1);
  if (mv !== -1) { board[mv] = 2; return check_winner(); }
  // Center
  if (board[4] === 0) { board[4] = 2; return check_winner(); }
  // Corners
  let corners = [0, 2, 6, 8];
  for (let i = 0; i < 4; i++) if (board[corners[i]] === 0) { board[corners[i]] = 2; return check_winner(); }
  // First empty
  for (let i = 0; i < 9; i++) if (board[i] === 0) { board[i] = 2; return check_winner(); }
  return check_winner();
}

function renderBoard(){
  const boardEl = el('board');
  boardEl.innerHTML = '';
  for (let i = 0; i < 9; i++){
    const btn = document.createElement('button');
    btn.className = 'cell';
    btn.dataset.idx = i;
    const v = get_cell(i);
    btn.textContent = v === 1 ? 'X' : v === 2 ? 'O' : '';
    btn.addEventListener('click', onCellClick);
    boardEl.appendChild(btn);
  }
}

function setStatus(s){ el('status').textContent = s; }

function onCellClick(e){
  const idx = parseInt(e.currentTarget.dataset.idx);
  const res = player_move(idx);
  if (res === -1){ setStatus('Invalid move'); return; }
  renderBoard();
  if (res === 1){ setStatus('You win!'); return; }
  if (res === 3){ setStatus('Draw'); return; }
  // computer
  const cres = computer_move();
  renderBoard();
  if (cres === 2){ setStatus('Computer wins'); return; }
  if (cres === 3){ setStatus('Draw'); return; }
  setStatus('Your turn');
}

function reset(){ reset_board(); renderBoard(); setStatus('Your turn'); }

// Initialize on page load
window.addEventListener('DOMContentLoaded', function() {
  reset();
  el('reset').addEventListener('click', reset);
});
