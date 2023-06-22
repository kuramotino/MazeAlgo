#pragma once
#include "Planning.h"

namespace Algorizm
{
	class Pass_Generator
	{
		int pass[255];
		int passcount=0;
		Planning* my_plan;

		int OO90_R[3] = { 1,-3,1 };
		int OO90_L[3] = { 1,-2,1 };
		int OO180_R[4] = { 1,-3,-3,1 };
		int OO180_L[4] = { 1,-2,-2,1 };

	public:
		void SetPlan(Planning* bu_plan);
		void M_Pass(int goal_size, POS* goal_pos);//pass‚ğ¶¬‚·‚é
		int DecodePass();//pass‚©‚çŸ‚Ìs“®‚ğ•Ô‚·ŠÖ”
		void InitPassCount();//pass‚ğ‰Šú‰»‚·‚éŠÖ”
		void Comp_Pass(int* tar_pass, int pass_size, int setpassnum);//pass‚ğˆ³k‚·‚éŠÖ”
		void St_Comp_Pass(void);//’¼ü‚Ìˆ³k
		void Conect_v_cal(int passcount);//’¼i‚ÌÚ‘±‘¬“x‚ğŒvZ
	};
}