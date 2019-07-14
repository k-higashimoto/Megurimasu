package lib.crap;

import java.util.stream.Stream;

public class ArrayElementTF {
    /**
     * 配列の要素を変換するためのクラス
     */

    public static int[] toIntFromStr(String[] StringArray) {
        /**
         * 文字列配列を整数配列に変換する
         * @param StringArray 変換したい文字列配列
         * @return IntegerArray 変換後の整数配列
         */

        int[] IntegerArray = Stream.of(StringArray).mapToInt(Integer::parseInt).toArray();
        return IntegerArray;
    }
}
