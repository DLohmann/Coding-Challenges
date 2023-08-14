
# Mathworks Matlab "Cody" Question: [Problem 1319. Leap years on other planets](https://www.mathworks.com/matlabcentral/cody/problems/1319-leap-years-on-other-planets)

<div class="SectionBlock containment"><div class="paragraphNode wrappable" style="text-align: left; width: 686px;"><span class="textBox"><span class="textWrapper">A year is a leap year if it is divisible by 4, but not if it is divisible by 100, unless it is also divisible by 400. This means the average length of a calendar year is</span></span></div><div class="CodeBlock contiguous"><div class="lineNode mwRichTextComponentLine plainTextFixedSize"><span class="textBox"><span class="textWrapper">    365 + 1/4 - 1/100 + 1/400 = 365.2425 days</span></span></div></div><div class="paragraphNode wrappable" style="text-align: left; width: 686px;"><span class="textBox"><span class="textWrapper">which approximately matches the length of an actual year (the number of days it takes the earth to go around the sun once).</span></span></div><div class="paragraphNode wrappable" style="text-align: left; width: 686px;"><span class="textBox"><span class="textWrapper">Given p, the length of a year on another planet in units of days on that planet, and given that normal years have N days and leap years have N+1 days, where N=floor(p), find integer vector m&gt;0 defining leap years [years divisible by m(1) are leap years, but years divisible by m(2) are not, unless they are divisible by m(3), but then not if they are divisible by m(4), etc.] so that</span></span></div><div class="CodeBlock contiguous"><div class="lineNode mwRichTextComponentLine plainTextFixedSize"><span class="textBox"><span class="textWrapper">   p = N + 1/m(1) - 1/m(2) + 1/m(3) - 1/m(4) + </span><span class="textWrapper" style="color: rgb(14, 0, 255);">...</span></span></div></div><div class="paragraphNode wrappable" style="text-align: left; width: 686px;"><span class="textBox"><span class="textWrapper">Include enough terms so that this is correct to four decimal places. Note that m(i+1) should be an integer multiple of m(i). Results are not necessarily unique. For example, if p=365.2425 then m=[4 100 400] is an exact answer, but m=[4 132 13068] also could be used (and [4 132] gives 365.2424, a better approximation than [4 100], which gives 365.2400).</span></span></div></div>


### Test in Python:
```bash
python3 Mathworks_Cody/P_1319_Leap_years_on_other_planets/Leap_year_on_planet_test.py
```