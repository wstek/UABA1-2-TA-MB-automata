#ifndef TA_AUTOMATA_SRC_ENFA_H
#define TA_AUTOMATA_SRC_ENFA_H

#include "Automaton.h"

class DFA;
class NFA;
class RE;

class ENFA : public Automaton
{
	struct State
	{
		std::string name;
		std::map<char, std::set<State*>> transitions;
		bool accepting = false;
	};
	std::map<std::string, State*> states;
	State* start_state = nullptr;

public:
	ENFA();
	ENFA(const std::string& json_filename);
	~ENFA();

	bool load(const std::string& filename) override;
	json save() const override;
	void print() const override;
	void clear() override;

	void addState(const std::string& name, bool is_accepting) override;
	bool removeState(const std::string& name) override;
	bool setStartState(const std::string& new_start_state_name) override;
	bool addTransition(const std::string& s1_name, const std::string& s2_name, char a) override;
	bool removeTransition(const std::string& s1_name, char a) override;
	bool accepts(const std::string& string_w) const override;

	/* Modified subset construction */
	DFA toDFA();
	NFA toNFA(); // new algorithm
	RE toRE(); // finished

	bool checkLegality() const override;
	std::string genDOT() const override;

private:
	State* getState(const std::string& name) const;
};

#endif //TA_AUTOMATA_SRC_ENFA_H
