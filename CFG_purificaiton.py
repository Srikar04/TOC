from itertools import chain, combinations

def powerset(iterable):
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s) + 1))

def remove_lambda_productions(grammar):
    nullable = set()
    for non_terminal, rules in grammar.items():
        for rule in rules:
            if rule == "λ":
                nullable.add(non_terminal)

    new_grammar = {}
    for non_terminal, rules in grammar.items():
        new_rules = set()
        for rule in rules:
            if rule != "λ":
                nullable_symbols = [symbol for symbol in nullable if symbol in rule]
                for subset in powerset(nullable_symbols):
                    new_rule = rule
                    for symbol in subset:
                        new_rule = new_rule.replace(symbol, "", 1)
                    new_rules.add(new_rule)
        new_grammar[non_terminal] = list(new_rules)

    return new_grammar


def remove_unit_productions(grammar):
    def find_unit_productions():
        unit_productions = {}
        for non_terminal, rules in grammar.items():
            for rule in rules:
                if len(rule) == 1 and rule in grammar:
                    if non_terminal not in unit_productions:
                        unit_productions[non_terminal] = set()
                    unit_productions[non_terminal].add(rule)
        return unit_productions

    def transitive_closure(unit_productions):
        def visit(symbol, visited):
            if symbol not in visited:
                visited.add(symbol)
                if symbol in unit_productions:
                    for next_symbol in unit_productions[symbol]:
                        visit(next_symbol, visited)

        for non_terminal in unit_productions:
            visited = set()
            visit(non_terminal, visited)
            unit_productions[non_terminal] = visited - {non_terminal}


    unit_productions = find_unit_productions()
    transitive_closure(unit_productions)

    new_grammar = {}
    for non_terminal, rules in grammar.items():
        new_rules = []
        for rule in rules:
            if len(rule) != 1 or rule not in grammar:
                new_rules.append(rule)
            else:
                if non_terminal != rule:  # Avoid self-loops
                    for symbol in unit_productions[non_terminal]:
                        new_rules.extend([r for r in grammar[symbol] if r != symbol])  # Avoid adding unit productions again
        new_grammar[non_terminal] = new_rules

    return new_grammar


def remove_useless_symbols(grammar):
    reachable = set("S")

    added = True
    while added:
        added = False
        for non_terminal, rules in grammar.items():
            if non_terminal in reachable:
                for rule in rules:
                    for symbol in rule:
                        if symbol not in reachable and symbol in grammar:
                            reachable.add(symbol)
                            added = True

    new_grammar = {non_terminal: rules for non_terminal, rules in grammar.items() if non_terminal in reachable}

    return new_grammar

def remove_nongenerative_symbols(grammar):
    generative = set()
    
    def is_generative(rule):
        return all(symbol not in grammar or symbol in generative for symbol in rule)
    
    added = True
    while added:
        added = False
        for non_terminal, rules in grammar.items():
            if non_terminal not in generative:
                for rule in rules:
                    if is_generative(rule):
                        generative.add(non_terminal)
                        added = True
                        break

    new_grammar = {non_terminal: rules for non_terminal, rules in grammar.items() if non_terminal in generative}

    return new_grammar

def purify_cfg(grammar):
    grammar_without_lambda = remove_lambda_productions(grammar)
    grammar_without_unit = remove_unit_productions(grammar_without_lambda)
    grammar_without_useless = remove_useless_symbols(grammar_without_unit)
    purified_grammar = remove_nongenerative_symbols(grammar_without_useless)

    return purified_grammar

# Example usage 1:
grammar = {
    "S": ["AB", "BC"],
    "A": ["aA", "λ"],
    "B": ["bB", "λ"],
    "C": ["cC", "S"],
}

# Example usage 1:
# grammar = {
#     "S": ["Aa", "Bb", "λ"],
#     "A": ["Ba", "C"],
#     "B": ["Ab", "λ"],
#     "C": ["D"],
#     "D": ["E"],
#     "E": ["F"],
#     "F": ["G"],
#     "G": ["H"],
#     "H": ["I"],
#     "I": ["C"],
# }



purified_grammar = purify_cfg(grammar)
print(purified_grammar)
