package test;

import lib.crap.ConversionDirPos;
import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThat;

public class ConversionDirPosTest {
    /**
     * ConversionDirPosクラスのtoDirFromPosメソッドが正しく動作するか
     * 確かめるためのテストクラス
     */

    @Test
    public void testToDirFromPos() {

        HashMap<Integer, int[]> positions = new HashMap<Integer,int[]>();
        positions.put(0, new int[]{5, 5});
        positions.put(1, new int[]{6, 5});
        positions.put(2, new int[]{6, 6});
        positions.put(3, new int[]{5, 6});
        positions.put(4, new int[]{4, 6});
        positions.put(5, new int[]{4, 5});
        positions.put(6, new int[]{4, 4});
        positions.put(7, new int[]{5, 4});
        positions.put(8, new int[]{6, 4});

        for (Map.Entry<Integer, int[]> entry: positions.entrySet()) {

            int tileX1 = 5;
            int tileY1 = 5;
            int[] position2 = entry.getValue();
            int tileX2 = position2[0];
            int tileY2 = position2[1];

            int direction = ConversionDirPos.toDirFromPos(
                    tileX1,
                    tileY1,
                    tileX2,
                    tileY2
            );
            int expect = entry.getKey();

            assertEquals(expect, direction);
        }
    }
}
