make fclean -C mandatory;
make fclean -C bonus;
git add .;
read -p "Enter commit message: " msg_push;
git commit -m "$msg_push";
git push origin ${USER};