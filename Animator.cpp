#include "Animator.h"

void Animator::tick(double delta) {

	if((time+=delta) > current_anim->duration[cur]) {
		time = 0;
		if (++cur > current_anim->size) {
			cur = 0;
			if (next_anim)
				setAnimatable(next_anim);
		}
	}

}
