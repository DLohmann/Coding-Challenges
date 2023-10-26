
# Pair Sums
#### Question from Meta interview prep ([Link to problem](https://www.metacareers.com/profile/coding_practice_question/?problem_id=840934449713537))

<div data-contents="true"><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="61v8r-0-0"><div data-offset-key="61v8r-0-0" class="_1mf _1mj"><span data-offset-key="61v8r-0-0"><span data-text="true">Given a list of </span></span><span data-offset-key="61v8r-0-1" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">n</span></span><span data-offset-key="61v8r-0-2"><span data-text="true"> integers </span></span><span data-offset-key="61v8r-0-3" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">arr[0..(n-1)]</span></span><span data-offset-key="61v8r-0-4"><span data-text="true">, determine the number of different pairs of elements within it which sum to </span></span><span data-offset-key="61v8r-0-5" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">k</span></span><span data-offset-key="61v8r-0-6"><span data-text="true">.</span></span></div></div><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="f6nul-0-0"><div data-offset-key="f6nul-0-0" class="_1mf _1mj"><span data-offset-key="f6nul-0-0"><span data-text="true">If an integer appears in the list multiple times, each copy is considered to be different; that is, two pairs are considered different if one pair includes at least one array index which the other doesn't, even if they include the same values.</span></span></div></div><h1 class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="f9vg2-0-0"><div data-offset-key="f9vg2-0-0" class="_1mf _1mj"><span data-offset-key="f9vg2-0-0"><span data-text="true">Signature</span></span></div></h1><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="1pics-0-0"><div data-offset-key="1pics-0-0" class="_1mf _1mj"><span data-offset-key="1pics-0-0" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">int numberOfWays(int[] arr, int k)</span></span></div></div><h1 class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="7ao7d-0-0"><div data-offset-key="7ao7d-0-0" class="_1mf _1mj"><span data-offset-key="7ao7d-0-0"><span data-text="true">Input</span></span></div></h1><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="1djt6-0-0"><div data-offset-key="1djt6-0-0" class="_1mf _1mj"><span data-offset-key="1djt6-0-0" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">n</span></span><span data-offset-key="1djt6-0-1"><span data-text="true"> is in the range [1, 100,000].
Each value </span></span><span data-offset-key="1djt6-0-2" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">arr[i]</span></span><span data-offset-key="1djt6-0-3"><span data-text="true"> is in the range [1, 1,000,000,000].
</span></span><span data-offset-key="1djt6-0-4" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">k</span></span><span data-offset-key="1djt6-0-5"><span data-text="true"> is in the range [1, 1,000,000,000].</span></span></div></div><h1 class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="bgt7f-0-0"><div data-offset-key="bgt7f-0-0" class="_1mf _1mj"><span data-offset-key="bgt7f-0-0"><span data-text="true">Output</span></span></div></h1><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="5hp5r-0-0"><div data-offset-key="5hp5r-0-0" class="_1mf _1mj"><span data-offset-key="5hp5r-0-0"><span data-text="true">Return the number of different pairs of elements which sum to </span></span><span data-offset-key="5hp5r-0-1" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">k</span></span><span data-offset-key="5hp5r-0-2"><span data-text="true">.</span></span></div></div><h1 class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="c6p82-0-0"><div data-offset-key="c6p82-0-0" class="_1mf _1mj"><span data-offset-key="c6p82-0-0"><span data-text="true">Example 1</span></span></div></h1><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="3dhi1-0-0"><div data-offset-key="3dhi1-0-0" class="_1mf _1mj"><span data-offset-key="3dhi1-0-0" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">n</span></span><span data-offset-key="3dhi1-0-1"><span data-text="true"> = 5
</span></span><span data-offset-key="3dhi1-0-2" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">k</span></span><span data-offset-key="3dhi1-0-3"><span data-text="true"> = 6
</span></span><span data-offset-key="3dhi1-0-4" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">arr</span></span><span data-offset-key="3dhi1-0-5"><span data-text="true"> = [1, 2, 3, 4, 3]
</span></span><span data-offset-key="3dhi1-0-6" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">output</span></span><span data-offset-key="3dhi1-0-7"><span data-text="true"> = 2</span></span></div></div><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="8gf8i-0-0"><div data-offset-key="8gf8i-0-0" class="_1mf _1mj"><span data-offset-key="8gf8i-0-0"><span data-text="true">The valid pairs are 2+4 and 3+3.</span></span></div></div><h1 class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="39ksf-0-0"><div data-offset-key="39ksf-0-0" class="_1mf _1mj"><span data-offset-key="39ksf-0-0"><span data-text="true">Example 2</span></span></div></h1><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="4gdrv-0-0"><div data-offset-key="4gdrv-0-0" class="_1mf _1mj"><span data-offset-key="4gdrv-0-0" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">n</span></span><span data-offset-key="4gdrv-0-1"><span data-text="true"> = 5
</span></span><span data-offset-key="4gdrv-0-2" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">k</span></span><span data-offset-key="4gdrv-0-3"><span data-text="true"> = 6
</span></span><span data-offset-key="4gdrv-0-4" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">arr</span></span><span data-offset-key="4gdrv-0-5"><span data-text="true"> = [1, 5, 3, 3, 3]
</span></span><span data-offset-key="4gdrv-0-6" style="font-family: monospace; overflow-wrap: break-word;"><span data-text="true">output</span></span><span data-offset-key="4gdrv-0-7"><span data-text="true"> = 4</span></span></div></div><div class="_8z_j" data-block="true" data-editor="5d67l" data-offset-key="bdljp-0-0"><div data-offset-key="bdljp-0-0" class="_1mf _1mj"><span data-offset-key="bdljp-0-0"><span data-text="true">There's one valid pair 1+5, and three different valid pairs 3+3 (the 3rd and 4th elements, 3rd and 5th elements, and 4th and 5th elements).</span></span></div></div></div>


## To run:
```bash
g++ Pair_Sums.cpp -o Pair_Sums
./Pair_Sums
```