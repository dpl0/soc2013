#!/bin/sh
# Script to remove shall clauses.
#
# $FreeBSD: soc2013/dpl/head/share/examples/mdoc/deshallify.sh 140035 2005-01-10 18:54:55Z ru $
#
sed -e 's/s shall define/s define/g' \
    -e 's/shall define/defines/g' \
    -e 's/shall attempt/attempts/g' \
    -e 's/shall include/includes/g' \
    -e 's/shall return zero and have/returns zero and has/g' \
    -e 's/shall return/returns/g' \
    -e 's/shall also include/also includes/g' \
    -e 's/pipe or FIFO shall be /pipe of FIFO are /g' \
    -e 's/s shall be /s are /g' \
    -e 's/shall be /is /g' \
    -e 's/s shall create/s create/g' \
    -e 's/shall create /creates /g' \
    -e 's/shall perform/performs/g' \
    -e 's/shall affect the/affect the/g' \
    -e 's/s shall have/s have/g' \
    -e 's/shall have/has/g' \
    -e 's/shall transfer/transfers/g' \
    -e 's/shall block/blocks/g' \
    -e 's/shall not block/does not block/g' \
    -e 's/shall occur/occurs/g' \
    -e 's/shall complete/complete/g' \
    -e 's/shall mark for update/marks for update/g' \
    -e 's/s shall fail/s fail/g' \
    -e 's/shall fail/fails/g' \
    -e 's/s shall generate/s generate/g' \
    -e 's/shall generate/generates/g' \
    -e 's/shall place/places/g' \
    -e 's/s shall default/s default/g' \
    -e 's/shall default/defaults/g' \
    -e 's/pplications shall ensure/pplications must ensure/g' \
    -e 's/pplication shall ensure/pplication must ensure/g' \
    -e 's/shall always begin/always begins/g' \
    -e 's/s shall begin /s begin /g' \
    -e 's/shall begin /begins /g' \
    -e 's/shall always contain /always contains /g' \
    -e 's/shall produce/produces/g' \
    -e 's/shall appear/appears/g' \
    -e 's/s shall be$/s are/g' \
    -e 's/shall be$/is/g' \
    -e 's/which shall result /which results /g' \
    -e 's/s shall not/s are not/g' \
    -e 's/shall not be/is not/g' \
    -e 's/shall not/is not/g' \
    -e 's/s shall behave/s behave/g' \
    -e 's/shall behave/behaves/g' \
    -e 's/shall specify/specifies/g' \
    -e 's/s shall override/s override/g' \
    -e 's/shall override/overrides/g' \
    -e 's/shall apply /applies /g' \
    -e 's/s shall start/s start/g' \
    -e 's/shall start /starts /g' \
    -e 's/s shall affect/s affect/g' \
    -e 's/shall affect/affects/g' \
    -e 's/s shall indicate/s indicate/g' \
    -e 's/shall indicate/indicates/g' \
    -e 's/shall set /set /g' \
    -e 's/s shall recognize/s recognize/g' \
    -e 's/shall recognize /recognizes /g' \
    -e 's/shall also be /is also /g' \
    -e 's/s shall enter/s enter/g' \
    -e 's/shall enter /enters /g' \
    -e 's/shall take /take /g' \
    -e 's/they shall only take /they only take /g' \
    -e 's/shall consist /consist /g' \
    -e 's/s shall cause/s cause/g' \
    -e 's/shall cause/causes/g' \
    -e 's/s shall replace/s replace/g' \
    -e 's/shall replace/replaces/g' \
    -e 's/shall become/becomes/g' \
    -e 's/shall each consist/each consist/g' \
    $1 > $1.x
