
# MST-BÇ USV Barbaros Kontrol Yazılımı

2023 mst-bç kapsamında geliştirilen barbaros otonom su üstü aracının ros tabanlı kontrol yazılımı.


## Özellikler

- Gazebo entegrasyonu
- Simülasyon
- Klavye kontrolü
- Ubuntu 20.4 ve ros noetic uyumluluğu

  
## Yükleme ve Çalıştırma

Ros sitesinden ros noetic sürümünü yükleyiniz: 
http://wiki.ros.org/noetic/Installation/Ubuntu

**veya yükleme için aşağıdaki kodları sırası ile çalıştırınız:**

	sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

	sudo apt install curl

	curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

	sudo apt update

	sudo apt install ros-noetic-desktop-full

	source /opt/ros/noetic/setup.bash

	echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
	
	source ~/.bashrc

	sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential

	sudo apt install python3-rosdep

	sudo rosdep init

	rosdep update

Bu aşamadan sonra ros kurulmuş olması gerekmektedir. 
Sonraki aşamalarda ros için daha uygun terminal olan "terminator" indirmek için;

    sudo apt-get install terminator
ardından ros kodlarını koymak için istediğiniz bir dizine(home dizini olması önerilir) aşağıdaki kodları yazıp klasör oluşturunuz.

    mkdir catkin_ws 
    cd catkin_ws
    mkdir src
    
ardından belirlediğiniz dizinde catkin_ws klasörü içinde ise src klasörü olduğunu kontrol ediniz.

terminalde catkin_ws yoluna giderek 

    catkin_make 

komutunu çalıştırarak dizini derleyiniz.

Ardından ;

catkin_ws/src içine "**mst_uuv**" github dosyasını indiriniz
(Github desktop kullanımını tavsiye ederiz.
Github desktop için: https://gist.github.com/berkorbay/6feda478a00b0432d13f1fc0a50467f1)

Ardından gerekli bazı paketler için;

	sudo apt-get install ros-noetic-serial
	pip install scipy
	sudo apt-get install ros-noetic-rosserial-arduino ros-noetic-rosserial-embeddedlinux ros-noetic-rosserial-windows ros-noetic-rosserial-server ros-noetic-rosserial-python

catkin_ws yoluna gidin 
    
    catkin_make 

komutunu çalıştırarak dizini derleyiniz. Bu aşamada derlemenin hatasız olması gerekmektedir.

terminalde en ana dizinde;

         sudo gedit ~/.bashrc
komutu çalıştırılır.

	source /home/user/catkin_ws/devel/setup.bash

satırları sona yapıştırılır(user yerine kullanıcı adı)

Bu aşamadan sonra modüllerin başarıyla yüklenmiş olması gerekmektedir.

Denemek için;

    roslaunch uuv_gazebo start_pid_demo_barbaros.launch
## Kullanım/Örnek komutlar

- Dünyayı açmak için:

		roslaunch uuv_gazebo start_pid_demo_barbaros.launch 

- Waypoint göndermek için:

		roslaunch uuv_control_utils send_waypoints_file.launch uuv_name:=barbaros interpolator:=linear

- Klavyeden yönetmek için: 

		roslaunch uuv_teleop uuv_keyboard_teleop.launch uuv_name:=barbaros

- Tf ağacını görmek için:

		rosrun rqt_tf_tree rqt_tf_tree 

- Pid parametrelerini değiştirmek için catkin_ws/src/mst_uuv/uuv_control/uuv_trajectory_control/config/controllers/pid/barbaros/config 

	dosyasının içindeki parametreleri değiştirin ve 

		roslaunch uuv_gazebo pid_parameter_load.launch 

- Pose ayarlamak için:

		rosservice call /gazebo/set_model_state "model_state:

- Mpu ile oryantasyon ayarlamak için:

		rosrun mpu6050_serial_to_imu mpupose

		roslaunch mpu6050_serial_to_imu mpupose.launch 

Not: Mpu ile oryantasyon ayarlamak için arduinoya gerekli kodun yüklenmesi ve bağlantılarının yapılması gerekmektedir. Ayrıca arduinoyu bağladığınız portu belirtmeyi unutmayınız.
## Yazarlar ve Teşekkür

- Danışman: [@Cenk Ulu](https://avesis.yildiz.edu.tr/cenkulu/dokumanlar) 
- [@berkanyasar](https://www.github.com/berkanyasar) tasarım ve geliştirme için.
- [@kabilemre](https://www.github.com/kabilemre) test ve kontrol için.
- [@scbektas](https://www.github.com/scbektas) kontrol mimarisi için.
- [@Whitte10](https://www.github.com/Whitte10) kontrol yazılımı için.
