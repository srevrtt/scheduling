module scheduling

#include "../SchedulingiOS/SchedulingiOS/src/include/v_bridge.h"

fn C.draw_rect(x int, y int, w int, h int, r int, g int, b int)

@[export: 'sch_loop']
fn sch_loop() {
	C.draw_rect(10, 10, 100, 100, 150, 150, 150)
}
