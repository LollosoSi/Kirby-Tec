#pragma once

namespace KA
{
	class Enemy;
}

class KA::Enemy
{
	protected:
		// attributes
		
		bool _haspower;
		bool _canhurt;
		// state flags
		bool _smashed;
		bool _inhaled;
		bool _dead;
	public:
		// advance only when visible to Kirby
		

};