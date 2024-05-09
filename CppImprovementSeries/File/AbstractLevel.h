#pragma once

#include <memory>
#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>

namespace Menu {

	template<typename TActionCode>
	class AbstractLevel
	{
	public:
		using MenuSymbol = char;
		using Description = std::string;
		using AbstractLevelPtr = std::shared_ptr<AbstractLevel<TActionCode>>;
		using ActionResult = std::pair<AbstractLevelPtr, TActionCode>;
	protected:
		using ParentPtr = std::weak_ptr<AbstractLevel>;
	public:
		AbstractLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const TActionCode& mCode);
		AbstractLevel(const AbstractLevel& other) = delete;
		AbstractLevel& operator=(const AbstractLevel& other) = delete;
		AbstractLevel(AbstractLevel&& other) = default;
		AbstractLevel& operator=(AbstractLevel&& other) = default;
		virtual ~AbstractLevel() = default;
	public:
		virtual ActionResult makeAction() const = 0;
		void printLevel() const;
	public:
		MenuSymbol getSymbol() const {
			return mSymbol;
		}
		MenuSymbol getBackSymbol() const {
			return 'b';
		}
		MenuSymbol getExitSymbol() const {
			return 'e';
		}
	protected:
		MenuSymbol mSymbol;
		Description mDescription;
		ParentPtr mParent;
		TActionCode mCode;
	};

	template<typename TActionCode>
	AbstractLevel<TActionCode>::AbstractLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const TActionCode& code)
		: mSymbol(symbol)
		, mDescription(description)
		, mParent(parent)
		, mCode(code)
	{
		if (getBackSymbol() == mSymbol || getExitSymbol() == mSymbol) {
			throw std::runtime_error("Incorrect menu symbol provided");
		}
	}

	template<typename TActionCode>
	void AbstractLevel<TActionCode>::printLevel() const {
		std::cout << mSymbol << " - " << mDescription;
	}
}