
open List;;


let rec subset a b =
    match a with
        [] -> true
      | _  -> if mem (List.hd a) b then
                  let a_remaining = List.tl a in
                  subset a_remaining b
              else 
                  false
;;

(*
subset [3] [3;5];;       (* true *)
subset [3;5] [3;5;7];;   (* true *)
subset [3;5] [3;5];;     (* true *)

subset [3] [];;          (* false *)
subset [] [3];;          (* true *)
subset [3;5;7] [5;7];;   (* false *)
*)

let rec proper_subset a b =
    match a with
        [] -> if b = [] then false else true
      | _  -> if mem (List.hd a) b then
                  let a_remaining = List.filter (fun x -> x <> (List.hd a)) a in
                  let b_remaining = List.filter (fun x -> x <> (List.hd a)) b in
                  proper_subset a_remaining b_remaining
              else 
                  false
;;


(*
proper_subset [3] [3;5];;       (* true *)
proper_subset [3;5] [3;5;7];;   (* true *)
proper_subset [3;5] [3;5];;     (* false *)

proper_subset [3] [];;          (* false *)
proper_subset [] [3];;          (* true *)
proper_subset [3;5;7] [5;7];;   (* false *)
*)

let rec equal_sets a b =
    if subset a b && not (proper_subset a b) then true
    else false
;;

(*
equal_sets [3] [3;5];;       (* false *)
equal_sets [3;5] [3;5;7];;   (* false *)
equal_sets [3;5] [3;5];;     (* true *)

equal_sets [3] [];;          (* false *)
equal_sets [] [3];;          (* false *)
equal_sets [3;5;7] [5;7];;   (* false *)
equal_sets [] [];;           (* true  *)
*)


let rec computed_fixed_point eq f x =
    if eq (f x) x = true then x 
    else
        let f_of_x = f x in
        computed_fixed_point eq f f_of_x
;;

(* type declaration for terminal / nonterminal *)

type ('nonterminal, 'terminal) symbol = 
  | N of 'nonterminal
  | T of 'terminal

(* returns if a value in the terminals list is T, or a member of the known terminals list *)
let rec isT known_terminals term =
    match term with 
      | N n -> (* check if present in the known terminals *)
            if List.mem_assoc n known_terminals then true else false
      | T _ -> true
;;

(* subhelper for populate_term_list; parses a rule and returns true/false if it 
   terminates (using the isT function)
*)
let rec rule_parser known_terminals rule = 
    match rule with (a, terminal_list) ->
        if List.for_all (isT known_terminals) terminal_list then true else false
;;

(* helper function; populates a list of rules in the grammarthat are known to terminate.
   returns the list of known terminals.
*)
let rec populate_term_list known_terminals rules_list pre_size = 
    let new_known = List.filter (rule_parser known_terminals) rules_list in 
    let post_size = List.length new_known in
    if pre_size = post_size then new_known (*done*) 
    else populate_term_list new_known rules_list post_size;
;;


(* reorder of List.filter to make it work in my function *)
let mem_filter the_list item = 
    if List.mem item the_list then true
    else false
;;

(* filter_blind_alleys populates a list of known terminals, first adding the rules
   that only have T in their terminal list and working backwards. When a pass is made 
   that creates no size difference in the known_terminals list, the function terminates
   and returns the known_terminals list.
*)

let rec filter_blind_alleys g = 
    match g with (start, rules_list) ->
        let terminating_rules = populate_term_list [] rules_list (List.length []) in
        (* now use the known terminals list to shorten g + get things in order *)
        let valid_rules = List.filter (mem_filter terminating_rules) rules_list in
        
        (start, valid_rules)
;;


