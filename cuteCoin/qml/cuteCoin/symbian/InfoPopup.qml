import QtQuick 1.0
import com.nokia.extras 1.0

InfoBanner {
    id: infoBanner
    text: "Received 0.05 BTC"
    iconSource: "icons/list_icon_bitcoin.svg"

    function showPopup(icon, message) {
        if (icon == "ready") infoBanner.iconSource = "icons/list_icon_ready.svg"
        if (icon == "bitcoin") infoBanner.iconSource = "icons/list_icon_bitcoin.svg"
        infoBanner.text = message;
        infoBanner.open();
    }
}
