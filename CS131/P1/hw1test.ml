let my_subset_test0 = subset [3] [3;5]       (* true *)
let my_subset_test1 = subset [3;5] [3;5;7];;   (* true *)
let my_subset_test2 = subset [3;5] [3;5];;     (* true *)
let my_subset_test3 = not (subset [3] []);;          (* false *)
let my_subset_test4 = subset [] [3];;          (* true *)
let my_subset_test5 = not (subset [3;5;7] [5;7]);;   (* false *)


let my_proper_subset_test0 = proper_subset [3] [3;5];;       (* true *)
let my_proper_subset_test1 = proper_subset [3;5] [3;5;7];;   (* true *)
let my_proper_subset_test2 = not (proper_subset [3;5] [3;5]);;     (* false *)

let my_proper_subset_test3 = not (proper_subset [3] []);;          (* false *)
let my_proper_subset_test4 = proper_subset [] [3];;          (* true *)
let my_proper_subset_test5 = not (proper_subset [3;5;7] [5;7]);;   (* false *)

let my_equal_test0 = not (equal_sets [3] [3;5]);;       (* false *)
let my_equal_test1 = not (equal_sets [3;5] [3;5;7]);;   (* false *)
let my_equal_test2 = equal_sets [3;5] [3;5];;     (* true *)
let my_equal_test3 = not (equal_sets [3] []);;          (* false *)
let my_equal_test4 = not (equal_sets [] [3]);;          (* false *)
let my_equal_test5 = not (equal_sets [3;5;7] [5;7]);;   (* false *)
let my_equal_test6 = equal_sets [] [];;           (* true  *)

let my_computed_fixed_point_test0 = computed_fixed_point (=) (fun x -> x*x - 3*x +4) 1 = 2;;
let my_computed_fixed_point_test1 = computed_fixed_point (=) (fun x -> x/. 2.) 2. = 0.;;

type test_nonterminals_0 = 
    | Dude | Buddy | Friend
let friend_rules = 
    [ Dude, [N Buddy];
      Buddy, [N Friend];
      Friend, [N Dude];
      Friend, [T"test"]
    ]
let my_filter_blind_alleys_test0 = filter_blind_alleys (Dude, friend_rules) = (Dude, friend_rules);;
let my_filter_blind_alleys_test1 =
    filter_blind_alleys (Buddy, List.tl friend_rules) = 
        (Buddy, [Buddy, [N Friend]; Friend, [T"test"]]);;

type test_nonterminals_1 = 
    | Box | Microsoft | Google | Apple
let company_rules = 
    [ Apple, [N Google];
      Google, [N Microsoft];
      Google, [N Apple];
      Google, [T"b"];
      Microsoft, [T"c"];
      Box, [T"d"]
    ]

let my_filter_blind_alleys_test2 = filter_blind_alleys (Box, company_rules) = (Box, company_rules);;
let my_filter_blind_alleys_test3 = filter_blind_alleys (Google, List.tl company_rules) =
    (Google, 
    [Google, [N Microsoft];
     Google, [T"b"];
     Microsoft, [T"c"];
     Box, [T"d"]
    ]);;

