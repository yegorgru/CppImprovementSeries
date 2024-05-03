#pragma once

#include <memory>
#include <string>

namespace Menu {

	class AbstractLevel;
	using AbstractLevelPtr = std::shared_ptr<AbstractLevel>;

	class AbstractLevel
	{
	public:
		using MenuSymbol = char;
		using Description = std::string;
	protected:
		using ParentPtr = std::weak_ptr<AbstractLevel>;
	public:
		AbstractLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent);
		AbstractLevel(const AbstractLevel& other) = delete;
		AbstractLevel& operator=(const AbstractLevel& other) = delete;
		AbstractLevel(AbstractLevel&& other) = default;
		AbstractLevel& operator=(AbstractLevel&& other) = default;
		virtual ~AbstractLevel() = default;
	public:
		virtual AbstractLevelPtr makeAction() const = 0;
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
	};

}