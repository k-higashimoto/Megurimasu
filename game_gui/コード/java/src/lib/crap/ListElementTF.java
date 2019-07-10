package lib.crap;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ListElementTF {

    public static List<Integer> toIntFromStr(List<String> stringList) {
        /**
         * 文字列リストを整数リストに変換する
         * @param StringArray 変換したい文字列配列
         * @return IntegerArray 変換後の整数配列
         */

        List<Integer> integerList = stringList.stream().map(Integer::parseInt).collect(Collectors.toList());
        return integerList;
    }
}
