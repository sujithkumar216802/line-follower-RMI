import cv2
import time
import sys
font = cv2.FONT_HERSHEY_COMPLEX

i=0

cnt=0

cap = cv2.VideoCapture(0)
while True :
	ret,img = cap.read()

	#img = cv2.imread("shapes.jpg",cv2.IMREAD_COLOR)

	img = cv2.flip(img,1)

	gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

	blur = cv2.GaussianBlur(gray,(11,11),0)
	
	gaussian = cv2.adaptiveThreshold(blur,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,11,5)
    
    

	contours , _ = cv2.findContours(gaussian, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

   

	for cnt in contours :
        
		approx = cv2.approxPolyDP(cnt, 0.006*cv2.arcLength(cnt, True), True)
		cv2.drawContours(img, [approx], 0, (0,255,0), 1)
		x = approx.ravel()[0]
		y = approx.ravel()[1]
		if len(approx) == 3:
			cv2.putText(img, "Triangle", (x, y), font, 2, (0,255,0))
		elif len(approx) == 4:
			cv2.putText(img, "Rectangle", (x, y), font, 2, (0,255,0))
		elif len(approx) == 5:
			cv2.putText(img, "Pentagon", (x, y), font, 2, (0,255,0))
		else:
			cv2.putText(img, "Circle", (x, y), font, 2, (0,255,0))

        

    

  







    

	cv2.drawContours(img, contours, i, (0,255,0), 1)

	cv2.imshow('gray',gray)

	cv2.imshow('blur',blur)
	
	cv2.imshow('gaussian',gaussian)

	cv2.imshow('contours',img)

	if cv2.waitKey(1) & 0xFF == ord('q') :
		break
	elif cv2.waitKey(1) & 0xFF == ord('n') :
		i=i+1
	#time.sleep(0.5)

cap.release()
cv2.destroyAllWindows()


