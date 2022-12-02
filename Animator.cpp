#include "Animator.h"

void Animator::interruptOneShot() {
	
	if (next_anim != 0)
		if (repeat < ++repetitions) {
			setAnimatable(next_anim, savedtimescale);
			next_anim = 0;
			cur = 0;
		}
}

void Animator::tick(double delta) {

	if((time+=delta) > (current_anim->duration[cur]*timescale)) {
		time = 0;
		if (++cur == current_anim->size) {
			cur = 0;
			interruptOneShot();
		}
	}

}
