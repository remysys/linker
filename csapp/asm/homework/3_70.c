void proc(union ele *up) {
  up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y
}