#pragma once

#include "AbstractLevel.h"

#include <functional>

namespace Menu {

	template<typename TActionCode>
	class ActionLevel : public AbstractLevel<TActionCode>
	{
	public:
		using MenuSymbol = AbstractLevel<TActionCode>::MenuSymbol;
		using Description = AbstractLevel<TActionCode>::Description;
		using AbstractLevelPtr = AbstractLevel<TActionCode>::AbstractLevelPtr;
		using ActionResult = AbstractLevel<TActionCode>::ActionResult;
	public:
		ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const TActionCode& code);
		ActionLevel(const ActionLevel& other) = delete;
		ActionLevel& operator=(const ActionLevel& other) = delete;
		ActionLevel(ActionLevel&& other) = default;
		ActionLevel& operator=(ActionLevel&& other) = default;
		~ActionLevel() = default;
	public:
		ActionResult makeAction() const override;
	};

	template<typename TActionCode>
	ActionLevel<TActionCode>::ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const TActionCode& code)
		: AbstractLevel<TActionCode>(symbol, description, parent, code)
	{

	}

	template<typename TActionCode>
	AbstractLevel<TActionCode>::ActionResult ActionLevel<TActionCode>::makeAction() const {
		return { AbstractLevel<TActionCode>::mParent.lock(), AbstractLevel<TActionCode>::mCode };
	}
}