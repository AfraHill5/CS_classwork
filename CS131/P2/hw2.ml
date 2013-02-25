
open List;;

type ('nonterminal, 'terminal) symbol = 
  | N of 'nonterminal
  | T of 'terminal

(* CONVERT_GRAMMAR *)
let rec get_all_a rule_list a_list =
    match rule_list with 
      | [] -> a_list
      | h::t -> match h with (a,b) -> 
                if not (List.mem a a_list) then get_all_a t (a_list@[a])
                else get_all_a t a_list
;;

let rec get_all_b rule_list a_to_match = 
    match rule_list with 
      | [] -> []
      | h::t -> match h with (a,b) ->
                if a = a_to_match then b::(get_all_b t a_to_match)
                else get_all_b t a_to_match
;;

let rec convert_grammar gram1 = 
    match gram1 with (start, rule_list) ->
          let a_list = get_all_a rule_list [] in
          let new_rule_gram = List.map (get_all_b rule_list) a_list in
          let tuples = List.combine a_list new_rule_gram in

          
          (start, (function a -> List.assoc a tuples))
;;
(* DEBUG FOR CONVERT_GRAMMAR
type awksub_nonterminals =
  | Expr | Lvalue | Incrop | Binop | Num

let awksub_rules =
  [Expr, [T"("; N Expr; T")"];
   Expr, [N Num];
   Expr, [N Expr; N Binop; N Expr];
   Expr, [N Lvalue];
   Expr, [N Incrop; N Lvalue];
   Expr, [N Lvalue; N Incrop];
   Lvalue, [T"$"; N Expr];
   Incrop, [T"++"];
   Incrop, [T"--"];
   Binop, [T"+"];
   Binop, [T"-"];
   Num, [T"0"];
   Num, [T"1"];
   Num, [T"2"];
   Num, [T"3"];
   Num, [T"4"];
   Num, [T"5"];
   Num, [T"6"];
   Num, [T"7"];
   Num, [T"8"];
   Num, [T"9"]]

let awksub_grammar = Expr, awksub_rules

let my_gram = convert_grammar awksub_grammar
*)

(* PARSE_PREFIX *)

(* algorithm from section today:

You have a start expression
A
and a set of rules:
A -> [B1, b2, b3]
C -> [d1, d2, d3]
etc

To return a match you need two types of matchers. 
An "and" matcher, which returns if all the values passed in are accepted.
An "or" matcher, which returns if one of the values passed in is accepted.

Basically the OR matcher moves you up-down, and the AND moves you left/right.
So if you have 

start=A
A -> [N B], [N B N C]
B -> [T D1, T D2, N D3], [T D4 N D5]
C -> [T F]

First you call OR_matcher on the start value. You need to match NB | NB NC.
The or matcher checks all the values that are passed in. As soon as one returns true it returns.

To check each, first we "go into" B. For B to be true, one of its 2 possiblities needs to be true.
We need to call the OR matcher on B's possibilities. First, it goes into the first

T D1 T D2 N D3

For this to be accepted, all of the interior needs to be true. Thus we call the AND matcher here.
The AND matcher checks each of them in turn, and as soon as one doesn't work returns None. Else returns Some.

If the AND matcher returns None, the function goes up a level back to the OR and tries the next B value:

T D4 N D5

The AND matcher is called on each of these. If they all return, this is true and we can return some. Else we
have to break again and go back to A.

The first OR match on A failed so we go to the next one
N B N C

We call the AND on these. Go into B, etc. Go into C, etc.

*)


let rec rule_matcher rule_list curr rule rem_rules frag deriv =
    if List.length rem_rules >= List.length frag then None else
        (*impossible to match all fragments if length is off*)
    match rule with
      | T term -> 
        if term = (List.hd frag) then  (*terminal which matches first value in fragment *)
            (* need to apply the acceptor and return its value.
               couldn't get it to work.*)
            (*and_matcher rule_list curr rem_rules (List.tl frag) deriv (*acceptor*) *)
            Some(deriv, List.tl frag)
        else None
      | N nonterm -> 
          build_matcher rule_list nonterm frag deriv
                


and and_matcher rule_list curr l frag deriv  = 
    match l with
      |  [] -> Some(deriv, frag) (* returns the fragment part left *)
      |  h::t -> 
         let rule_status = rule_matcher rule_list curr h t frag deriv in
         match rule_status with
           |  None         -> None 
           |  Some(d,f) (* some *) -> 
                    (*and_matcher rule_list curr t (List.tl frag) d*)
                    and_matcher rule_list curr t (List.tl frag) d 
                                (* the problem is here^^ *)

and or_matcher rule_list curr ll frag deriv = 
   match ll with
     | []   -> None (* all "ors" failed *)
     | rhead::rtail ->
        let rules_and_matcher = and_matcher rule_list curr rhead frag deriv in
        match rules_and_matcher with
          |  None -> or_matcher rule_list curr rtail frag deriv
          |  Some(old_deriv,frag_part_remaining) ->(* matched part of the fragment *) 
                let d = List.append [(curr,rhead)] old_deriv in (*get the deriv set *)
                Some(d, frag_part_remaining)
            


and build_matcher rule_list curr frag deriv = 
   match (rule_list curr) with
     |  []  -> None (* all "ors" failed *)
     |  rules ->
          or_matcher rule_list curr rules frag deriv
;;       
           


let rec parse_prefix gram acc frag = 
    match gram with (start, rule_list) ->
       let deriv = [] in
       let b = build_matcher rule_list start frag deriv in (*builds d and frag_part_remaining*)
       match b with
         |  None         -> None
         |  Some(d, frag_part_remaining) (* some *) -> acc d frag_part_remaining
;;

