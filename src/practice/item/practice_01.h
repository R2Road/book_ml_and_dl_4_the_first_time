#pragma once

#include "r2cm/r2cm_iItem.h"

namespace practice_01
{
	class _1 : public r2cm::iItem
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() const override;
	};
}