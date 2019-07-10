package lib.UIParts;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.TextField;
import javafx.util.Duration;

public class Timer {
    /**
     * タイマーのクラス
     */
    private Timeline timeline;
    private int second, minute;

    public Timer(TextField timer) {
        /**
         * タイマーを設定する
         */
        timeline = new Timeline(new KeyFrame(Duration.millis(1000), new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                second++;
                minute = (second % 3600) / 60;
                timer.setText(
                        String.format("%02d", minute)
                        + ":"
                        + String.format("%02d", second%60));
            }
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
    }

    public void play() {
        /**
         * タイマーの開始
         */

        timeline.play();
    }

    public void stop() {
        /**
         * タイマーのストップ
         */

        timeline.stop();
    }
}
