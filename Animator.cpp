#include "Animator.h"

void Animator::tick(double delta) {

	if((time+=delta) > mintime){
		time = 0;
		cur = cur + 1 < current_anim->size ? cur + 1 : 0;
	}

}
