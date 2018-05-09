"*.json" is not exactly a json file. It has many parts as "signature2json".
"func2indexMap" is "index2funcSignature".The signatures are same with those in "*.json".The index is in every pair_first.
"pair2varMap" is "pair2var".
"interGraph" is "pair1, pair2, [label]". "pair1|pair2" is in "pair2varMap"."[label]" may be "[pair3, pair4]". "pair3|pair4" is a coding way as pair_first is also in "func2indexMap" and pair_second is mapping to every node in a func_tree.
