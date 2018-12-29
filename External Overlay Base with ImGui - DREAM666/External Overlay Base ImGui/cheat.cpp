#include <cheat.h>

namespace Cheat {
	void LateUpdate() {
		while (true) {

			//Only execute when window is in focus
			if (Globals::tWnd == GetForegroundWindow()) {

			}


			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}

	void Update() {
		while (true) {

			//Only execute when window is in focus
			if (Globals::tWnd == GetForegroundWindow()) {

			}

			//Toggle Menu
			if (GetAsyncKeyState(0x2D)) {
				if (!Globals::bShowMenu) {
					long winlong = GetWindowLong(Globals::hWnd, GWL_EXSTYLE);

					if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST)
						SetWindowLong(Globals::hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
				}

				if (Globals::bShowMenu) {
					long winlong = GetWindowLong(Globals::hWnd, GWL_EXSTYLE);

					if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT)
						SetWindowLong(Globals::hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT);
				}
				Globals::bShowMenu = !Globals::bShowMenu;

				while (GetAsyncKeyState(0x2D)) {}
			}


			std::this_thread::sleep_for(std::chrono::milliseconds(32));
		}
	}
}