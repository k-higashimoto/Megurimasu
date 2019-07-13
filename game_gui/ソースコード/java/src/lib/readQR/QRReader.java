package lib.readQR;

import com.google.zxing.*;
import com.google.zxing.common.HybridBinarizer;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;


public class QRReader {
    /**
     * QRコードを解析するクラス
     */

    private BufferedImage qrImage;
    private String qrText;

    public QRReader(BufferedImage qrImage) {
        this.qrImage = qrImage;
    }

    public String readQR() {
        /**
         * QRコードを解析し、解析結果を文字列として返す
         * @return qrText QRコードの文字列
         */
        try {
            HybridBinarizer binarizer = new HybridBinarizer(
                    new RGBLuminanceSource(
                            qrImage.getWidth(),
                            qrImage.getHeight(),
                            qrImage.getRGB(
                                    0, 0,
                                    qrImage.getWidth(),
                                    qrImage.getHeight(),
                                    null,
                                    0,
                                    qrImage.getWidth()
                            )
                    )
            ) ;

            BinaryBitmap bitmap = new BinaryBitmap(binarizer) ;

            Reader reader = new MultiFormatReader() ;
            Result decodeResult = reader.decode(bitmap) ;

            qrText = decodeResult.getText() ;

        } catch ( FormatException | ChecksumException | NotFoundException e) {
            e.printStackTrace();
        } finally {
            return qrText;
        }
    }

    public String getQrText() {
        return qrText;
    }
}
